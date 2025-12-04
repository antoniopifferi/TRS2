module;

#include "src/gui/AppLogger.h"

#include "mhdefin.h"
#include "mhlib.h"
#include "errorcodes.h"

#include <vector>
#include <string>
#include <format>

// ErrHandler is still implemented in the legacy C code (Measure.c)
extern "C" void ErrHandler(int Device, int Code, char* Function);

export module SpcMharp;

import Spc;
import Globals;

// Histogram-only MultiHarp implementation of Spc
export class SpcMharp : public Spc
{
public:
    SpcMharp()
    {
        outText("SpcMharp constructed");
    }

    ~SpcMharp() override
    {
        outText("SpcMharp destroyed");
    }

protected:
    // ---- device-specific overrides ----

    // Equivalent of InitMharp(...) called for all boards
    void initDev() override
    {
        for (int ib = 0; ib < P.Num.Board; ++ib) {
            initBoard(ib);
        }
    }

    // Equivalent of CloseMharp()
    void closeDev() override
    {
        for (int ib = 0; ib < P.Num.Board; ++ib) {
            const int ret = MH_CloseDevice(ib);
            if (ret < 0) {
                ErrHandler(ERR_MHARP, ret, (char*)"MH_CloseDevice");
            }
        }
    }

    // Equivalent to Pause for MultiHarp: just stop the measurement
    void pauseDev() override
    {
        stopMeasurementOnAllBoards();
    }

    // Equivalent of ClearMharp()
    void clearDev() override
    {
        for (int ib = 0; ib < P.Num.Board; ++ib) {
            const int ret = MH_ClearHistMem(ib);
            if (ret < 0) {
                ErrHandler(ERR_MHARP, ret, (char*)"MH_ClearHistMem");
            }
        }
    }

    // Equivalent of StartMharp(...)
    void startDev() override
    {
        // In the original C code StartMharp is called with a Board index;
        // here we just mirror the same logic for each board, using MHARP_DEV0
        // as the device index for the actual measurement start.
        for (int ib = 0; ib < P.Num.Board; ++ib) {
            startBoard(ib);
        }
    }

    void restartDev() override
    {
        // For histogram mode, restart == start
        startDev();
    }

    // Equivalent of the SPC_MHARP branch in SpcTime(Time):
    // Spc::setTime(...) already sets P.Spc.TimeM (seconds).
    void setTimeDev(float seconds) override
    {
        // MultiHarp expects an integer acquisition time in ms.
        P.Spc.TimeMharp = static_cast<int>(seconds * 1000.0f + 0.5f);
    }

    // Equivalent of StopMharp(...)
    void stopDev() override
    {
        stopMeasurementOnAllBoards();
    }

    // Equivalent of WaitMharp(...)
    void waitDev() override
    {
        // Poll the CTC status until the measurement is finished
        int mod_state = 0;
        int ret = 0;
        do {
            ret = MH_CTCStatus(MHARP_DEV0, &mod_state);
            if (ret < 0) {
                ErrHandler(ERR_MHARP, ret, (char*)"MH_CTCStatus");
                break;
            }
        } while (mod_state == 0);
    }

    // Equivalent of GetDataMharp() for histogram mode
    void getDataDev() override
    {
        using std::size_t;

        // The library expects a buffer large enough for all detectors and bins
        std::vector<unsigned int> data(
            static_cast<size_t>(MHARP_MAX_DET) *
            static_cast<size_t>(MHARP_MAX_BIN));

        P.Spc.Overflow = false;

        const int nBoards = P.Num.Board;
        const int nDet = P.Num.Det;
        const int nChan = P.Chann.Num;

        for (int ib = 0; ib < nBoards; ++ib) {
            int ret = 0;

            if (nDet > MHARP_MINDET_SINGLETRANSFER) {
                // Single transfer not convenient: read all histograms at once
                ret = MH_GetAllHistograms(MHARP_DEV0, data.data());
                if (ret < 0) {
                    ErrHandler(ERR_MHARP, ret, (char*)"MH_GetAllHistograms");
                    continue;
                }
            }
            else {
                // Single transfer per detector
                for (int id = 0; id < nDet; ++id) {
                    ret = MH_GetHistogram(
                        MHARP_DEV0,
                        &data[static_cast<size_t>(id * nChan)],
                        id);
                    if (ret < 0) {
                        ErrHandler(ERR_MHARP, ret, (char*)"MH_GetHistogram");
                        break;
                    }
                }
            }

            // Copy into the generic data buffer D.Buffer[board][det*ch + ch]
            for (int id = 0; id < nDet; ++id) {
                for (int ic = 0; ic < nChan; ++ic) {
                    const size_t srcIdx = static_cast<size_t>(ic + id * nChan);
                    D.Buffer[ib][ic + id * nChan] =
                        static_cast<T_DATA>(data[srcIdx]);
                }
            }
        }
    }

private:
    // ---- helpers ----

    // Port of InitMharp(Board) – HISTOGRAM part only, GUI / FLOW removed
    void initBoard(int board)
    {
        char libVersion[8] = {};
        char hwSerial[8] = {};

        int    ret = 0;
        int    histLen = 0;
        double resolution = 0.0;

        // Take the configuration from the global parameter structure
        auto& mh = P.Spc.Mharp[board];

        outText(std::format("Initializing MultiHarp (histogram), board {}", board));

        // Library version
        ret = MH_GetLibraryVersion(libVersion);
        if (ret < 0) {
            ErrHandler(ERR_MHARP, ret, (char*)"MH_GetLibraryVersion");
            return;
        }
        outText(std::format("MultiHarp lib version: {}", libVersion));

        // Open the device and report the serial number
        ret = MH_OpenDevice(board, hwSerial);
        if (ret < 0) {
            ErrHandler(ERR_MHARP, ret, (char*)"MH_OpenDevice");
            return;
        }
        outText(std::format("MultiHarp serial: {}", hwSerial));

        // Operation mode: histogram only (MODE_HIST)
        ret = MH_Initialize(board, MODE_HIST, 0);
        if (ret < 0) {
            ErrHandler(ERR_MHARP, ret, (char*)"MH_Initialize");
            return;
        }

        // Histogram length and software offset
        ret = MH_SetHistoLen(board, mh.LenCode, &histLen);
        if (ret < 0) {
            ErrHandler(ERR_MHARP, ret, (char*)"MH_SetHistoLen");
            return;
        }

        ret = MH_SetOffset(board, mh.Offset);
        if (ret < 0) {
            ErrHandler(ERR_MHARP, ret, (char*)"MH_SetOffset");
            return;
        }

        // Start mode: standard software start (used for histogram + sync rate)
        ret = MH_SetMeasControl(MHARP_DEV0, MEASCTRL_SINGLESHOT_CTC, 1, 1);
        if (ret < 0) {
            ErrHandler(ERR_MHARP, ret, (char*)"MH_SetMeasControl");
            return;
        }

        // Sync channel configuration
        ret = MH_SetSyncDiv(board, mh.SyncDivider);
        if (ret < 0) {
            ErrHandler(ERR_MHARP, ret, (char*)"MH_SetSyncDiv");
        }

        ret = MH_SetSyncEdgeTrg(board, mh.SyncLevel, mh.SyncEdge);
        if (ret < 0) {
            ErrHandler(ERR_MHARP, ret, (char*)"MH_SetSyncEdgeTrg");
        }

        ret = MH_SetSyncChannelOffset(board, mh.SyncOffset);
        if (ret < 0) {
            ErrHandler(ERR_MHARP, ret, (char*)"MH_SetSyncChannelOffset");
        }

        // Input channels configuration (level, edge, offset, enable)
        for (int id = 0; id < P.Num.Det; ++id) {
            ret = MH_SetInputEdgeTrg(board, id,
                mh.InputLevel[id],
                mh.InputEdge[id]);
            if (ret < 0) {
                ErrHandler(ERR_MHARP, ret, (char*)"MH_SetInputEdgeTrg");
            }

            ret = MH_SetInputChannelOffset(board, id, mh.InputOffset[id]);
            if (ret < 0) {
                ErrHandler(ERR_MHARP, ret, (char*)"MH_SetInputChannelOffset");
            }

            // Enable detector channel
            ret = MH_SetInputChannelEnable(board, id, 1);
            if (ret < 0) {
                ErrHandler(ERR_MHARP, ret, (char*)"MH_SetInputChannelEnable");
            }
        }

        // Binning (time resolution)
        ret = MH_SetBinning(board, mh.Binning);
        if (ret < 0) {
            ErrHandler(ERR_MHARP, ret, (char*)"MH_SetBinning");
        }

        // Time calibration: resolution is the bin width in ps
        ret = MH_GetResolution(board, &resolution);
        if (ret < 0) {
            ErrHandler(ERR_MHARP, ret, (char*)"MH_GetResolution");
        }
        else {
            P.Spc.Calib = resolution;
            P.Spc.Factor = P.Spc.Calib * P.Spc.Scale;
        }

        // The original C code also did a short measurement here to obtain
        // the sync rate (P.Spc.Mharp[board].SyncRate) and set P.Spc.TimeInit.
        // Since you only asked for the HISTOGRAM modality and not the FLOW
        // engine, that extra pre-measurement is intentionally omitted.
    }

    // Port of StartMharp(Board)
    void startBoard(int board)
    {
        int ret = MH_SetMeasControl(board, MEASCTRL_SINGLESHOT_CTC, 1, 1);
        if (ret < 0) {
            ErrHandler(ERR_MHARP, ret, (char*)"MH_SetMeasControl");
            return;
        }

        ret = MH_StartMeas(MHARP_DEV0, P.Spc.TimeMharp);
        if (ret < 0) {
            ErrHandler(ERR_MHARP, ret, (char*)"MH_StartMeas");
        }
    }

    // Port of StopMharp(Board) applied to all boards
    void stopMeasurementOnAllBoards()
    {
        for (int ib = 0; ib < P.Num.Board; ++ib) {
            const int ret = MH_StopMeas(ib);
            if (ret < 0) {
                ErrHandler(ERR_MHARP, ret, (char*)"MH_StopMeas");
            }
        }
    }
};
