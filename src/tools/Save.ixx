module;
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <filesystem>
#include <functional>
#include <algorithm>
#include <ctime>
#include <format>

#include "src/gui/AppLogger.h"

export module Save;

import Const;
import Globals;
import Data;

// Forward declarations
export void EnterName(void);
export void CompileHeader(void);

// Helper date/time functions (return pointers to null-terminated strings)
static const char* DateStr() {
    static thread_local char buf[11]; // YYYY-MM-DD
    std::time_t t = std::time(nullptr);
    std::tm tm;
#ifdef _MSC_VER
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
    return buf;
}
static const char* TimeStr() {
    static thread_local char buf[9]; // HH:MM:SS
    std::time_t t = std::time(nullptr);
    std::tm tm;
#ifdef _MSC_VER
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::strftime(buf, sizeof(buf), "%H:%M:%S", &tm);
    return buf;
}

/* CLOSE FILE */
export void CloseDataFile(void) {
    if (!P.File.Save) return;
    if (P.File.File) {
        fclose(P.File.File);
        P.File.File = nullptr;
    }
    return;
}

/* INITIALIZE FILE */
export void InitDataFile(void) {
    long size = 0;
    if (!P.File.Save) {
        if (!askYesNo("NOT SAVING FILE", "You selected File.Save=FALSE. Do you Confirm you proceed without saving?")) {
            ErrHandler("Save", 1, "Error in selecting NOT SAVE");
            std::exit(1);
        }
        else return;
    }

    // Format Tag as zero-padded 4 digits and build Name/Path
    std::string tag = std::format("{:04}", P.File.Tag); // padding 4 digits to 0
    P.File.Name = P.File.Prefix + tag;
    P.File.Path = P.File.Dir + "\\" + P.File.Name + "." + P.File.Ext;
    outText("Initializing File ");
    outText(std::string(P.File.Path));
    outText(" ...");
    if (std::filesystem::exists(P.File.Path)) EnterName();

    // Open File
    P.File.File = fopen(P.File.Path.c_str(), "wb");
    outText(P.File.Path.c_str());
    if (P.File.File == NULL) {
        ErrHandler("Save", 2, "Error Creating File Data");
        std::exit(1);
    }
    else {
        outText("File created");
    }

    //**CompileHeader();
    //**while (fwrite(&D.Head, sizeof(D.Head), 1, P.File.File) < 1);
    //**fflush(P.File.File);
}


/* ENTER FILE NAME */
export void EnterName(void) {
    char newName[STRLEN] = {0};
    // Ask user for a new file name (without extension)
    const char* prompt = "ATTENTION! The file already exists. Enter new file name without extension";
    if (!getTextInput("Message", prompt, newName, STRLEN)) {
        std::exit(1);
    }
    // copy into P.File.Name and rebuild path
    P.File.Name = std::string(newName);
    std::filesystem::path p = std::filesystem::path(P.File.Dir) / (P.File.Name + "." + P.File.Ext);
    P.File.Path = p.string();
}

/* SAVE DATA TO FILE */
export void DataSave(void) {
    if (!P.File.Save) return;
    fwrite(D->ArchiveData.data(), sizeof(TYPE_DATA), D->NumSlice * D->NumElem, P.File.File);
    std::fflush(P.File.File);
}



/* COMPILE HEADER (COMMON PART) */
export void CompileHeader(void) {
    //int id, il;

    //// Version Info
    //D.Head.Ver[0] = (short)(-VER_DUE);
    //D.Head.Ver[1] = (short)(P.Mamm.Mamm ? VER_MAMM : VER_GEN);
    //D.Head.SubHeadVer = VER_UNO;

    //// General Info
    //D.Head.SubHeader = P.Info.SubHeader;
    //D.Head.SizeHeader = static_cast<long>(sizeof(D.Head));
    //D.Head.SizeSubHeader = static_cast<long>(sizeof(T_SUB));
    //D.Head.SizeData = static_cast<long>(sizeof(T_DATA));
    //D.Head.Kind = P.Info.Kind;
    //D.Head.Appl = P.Info.Appl;
    //D.Head.Oma = P.Oma.Oma;

    //// Time Info
    //strncpy(D.Head.Date, DateStr(), 10 + 1);
    //strncpy(D.Head.Time, TimeStr(), 8 + 1);

    //// Loop Info
    //for (il = 0; il < MAX_LOOP - 2; il++) {
    //    D.Head.LoopHome[il] = P.Loop[il + 2].Home;
    //    D.Head.LoopFirst[il] = P.Loop[il + 2].First;
    //    D.Head.LoopLast[il] = P.Loop[il + 2].Last;
    //    D.Head.LoopDelta[il] = P.Loop[il + 2].Delta;
    //    D.Head.LoopNum[il] = P.Loop[il + 2].Num;
    //}

    //// Spc Info	
    //// Note: original code used P.Bins.Num - ensure ChannS exists with member Num
    //D.Head.McaChannNum = static_cast<long>(P.Bins.Num);
    //D.Head.McaTime = P.Spc.TimeM;
    //D.Head.McaFactor = P.Spc.Factor;
    //D.Head.MeasNorm = FALSE;

    //// Frame Info
    //D.Head.PageNum = P.Num.Page;
    //D.Head.FrameNum = P.Frame.Num;
    //D.Head.RamNum = P.Ram.Num;

    //// Label Info
    //for (il = 0; il < LABEL_MAX; il++) {
    //    // D.Head.LabelName/Content are fixed-size C buffers in D.Head (do not change here).
    //    // Copy safely from std::string fields in P.Label (if they are std::string) or existing char buffers.
    //    strncpy(D.Head.LabelName[il], P.Label[il].Name, LABEL_NAMELEN);
    //    D.Head.LabelName[il][LABEL_NAMELEN - 1] = '\0';
    //    strncpy(D.Head.LabelContent[il], P.Label[il].Content, LABEL_CONTENTLEN);
    //    D.Head.LabelContent[il][LABEL_CONTENTLEN - 1] = '\0';
    //}

    //// Const Info	
    //D.Head.Constn = P.Const.N;
    //D.Head.ConstRho = P.Const.Rho;
    //D.Head.ConstThick = P.Const.Thick;

    //// Mamm Info
    //D.Head.MammHeader = VER_MAMM_HEADER;
    //for (id = 0; id < D2; id++) {
    //    D.Head.MammIdxFirst[id] = P.Mamm.Idx[id].First;
    //    D.Head.MammIdxLast[id] = P.Mamm.Idx[id].Last;
    //    D.Head.MammIdxTop[id] = P.Mamm.Idx[id].Top[MAMM_VIS];
    //    D.Head.MammRateMid[id] = static_cast<long>(P.Mamm.Rate.Mid[id]);
    //    D.Head.MammRateHigh[id] = static_cast<long>(P.Mamm.Rate.High[id]);
    //}
}