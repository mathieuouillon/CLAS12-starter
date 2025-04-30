#pragma once

// <fmt> headers
#include <fmt/core.h>
#include <fmt/ranges.h>

// C++ headers
#include <limits>
#include <map>
#include <unordered_map>
#include <vector>

// Project headers
#include <hipo4/bank.h>

namespace Core {
inline static auto load_bank_by_index(const hipo::bank& from_bank, const std::string& idx) -> std::map<int, std::vector<int>> {
    std::map<int, std::vector<int>> map;

    const int rows = from_bank.getRows();
    if (rows <= 0) return map;
    const char* idx_name = idx.data();
    constexpr int BATCH_SIZE = 16;

    for (int i_from = 0; i_from < rows; i_from += BATCH_SIZE) {
        const int end = std::min(i_from + BATCH_SIZE, rows);
        for (int j = i_from; j < end; j++) {
            int iTo = from_bank.get<float>(idx_name, j);
            auto& vec = map[iTo];
            if (vec.empty()) vec.reserve(16);
            vec.push_back(j);
        }
    }

    return map;
}

struct CherenkovBank {
    int sector = std::numeric_limits<int>::quiet_NaN();
    float nphe = std::numeric_limits<float>::quiet_NaN();
    float time = std::numeric_limits<float>::quiet_NaN();
    float path = std::numeric_limits<float>::quiet_NaN();
    float chi2 = std::numeric_limits<float>::quiet_NaN();
    float x = std::numeric_limits<float>::quiet_NaN();
    float y = std::numeric_limits<float>::quiet_NaN();
    float z = std::numeric_limits<float>::quiet_NaN();
    float dtheta = std::numeric_limits<float>::quiet_NaN();
    float dphi = std::numeric_limits<float>::quiet_NaN();
    int status = std::numeric_limits<int>::quiet_NaN();
};

inline auto read_Cherenkov_bank(const hipo::bank& REC_Cherenkov, const int pindex) -> CherenkovBank {
    auto map = load_bank_by_index(REC_Cherenkov, "pindex");
    CherenkovBank output;

    if (!map.contains(pindex)) return output;

    for (int i : map.at(pindex)) {
        if (REC_Cherenkov.get<int>("detector", i) != 15) continue;
        output.sector = REC_Cherenkov.get<int>("sector", i);
        output.nphe = REC_Cherenkov.get<float>("nphe", i);
        output.time = REC_Cherenkov.get<float>("time", i);
        output.path = REC_Cherenkov.get<float>("path", i);
        output.chi2 = REC_Cherenkov.get<float>("chi2", i);
        output.x = REC_Cherenkov.get<float>("x", i);
        output.y = REC_Cherenkov.get<float>("y", i);
        output.z = REC_Cherenkov.get<float>("z", i);
        output.dtheta = REC_Cherenkov.get<float>("dtheta", i);
        output.dphi = REC_Cherenkov.get<float>("dphi", i);
        output.status = REC_Cherenkov.get<int>("status", i);
    }

    return output;
}

struct CalorimeterBank {
    struct CalorimeterStruct {
        int sector = std::numeric_limits<int>::quiet_NaN();
        int layer = std::numeric_limits<int>::quiet_NaN();
        float energy = std::numeric_limits<float>::quiet_NaN();
        float time = std::numeric_limits<float>::quiet_NaN();
        float path = std::numeric_limits<float>::quiet_NaN();
        float chi2 = std::numeric_limits<float>::quiet_NaN();
        float x = std::numeric_limits<float>::quiet_NaN();
        float y = std::numeric_limits<float>::quiet_NaN();
        float z = std::numeric_limits<float>::quiet_NaN();
        float lu = std::numeric_limits<float>::quiet_NaN();
        float lv = std::numeric_limits<float>::quiet_NaN();
        float lw = std::numeric_limits<float>::quiet_NaN();
    };

    CalorimeterStruct pcal;
    CalorimeterStruct inner;
    CalorimeterStruct outer;
};

/**
 * @brief Reads and extracts calorimeter data for a given particle index from the REC_Calorimeter bank.
 * 
 * This function processes the REC_Calorimeter bank to retrieve calorimeter information
 * for a specific particle identified by its `pindex`. It organizes the data into a 
 * `CalorimeterBank` structure, which contains information about the preshower calorimeter (PCAL),
 * inner calorimeter (ECin), and outer calorimeter (ECout).
 * 
 * @param REC_Calorimeter The input hipo::bank containing calorimeter data.
 * @param pindex The particle index for which the calorimeter data is to be retrieved.
 * @return A `CalorimeterBank` structure containing the extracted calorimeter data. If no data
 *         is found for the given `pindex`, an empty `CalorimeterBank` is returned.
 * 
 * @details
 * - The function uses a helper lambda to populate the `CalorimeterStruct` fields for each
 *   calorimeter type.
 * - It maps the `pindex` to the corresponding rows in the bank and processes only those rows.
 * - Only entries with `detector` value of 7 are considered.
 * - The `layer` field determines the type of calorimeter:
 *   - Layer 1: Preshower calorimeter (PCAL)
 *   - Layer 4: Inner calorimeter (ECin)
 *   - Layer 7: Outer calorimeter (ECout)
 * - The function extracts various properties such as sector, layer, energy, time, path, chi2,
 *   and spatial coordinates (x, y, z) for each calorimeter type.
 */
inline auto read_Calorimeter_bank(const hipo::bank& REC_Calorimeter, const int pindex) -> CalorimeterBank {
    auto map = load_bank_by_index(REC_Calorimeter, "pindex");
    CalorimeterBank output;

    if (!map.contains(pindex)) return output;

    // Helper lambda to populate CalorimeterStruct
    auto populate_calorimeter_struct = [&](CalorimeterBank::CalorimeterStruct& cal_struct, int i) {
        cal_struct.sector = REC_Calorimeter.get<int>("sector", i);
        cal_struct.layer = REC_Calorimeter.get<int>("layer", i);
        cal_struct.energy = REC_Calorimeter.get<float>("energy", i);
        cal_struct.time = REC_Calorimeter.get<float>("time", i);
        cal_struct.path = REC_Calorimeter.get<float>("path", i);
        cal_struct.chi2 = REC_Calorimeter.get<float>("chi2", i);
        cal_struct.x = REC_Calorimeter.get<float>("x", i);
        cal_struct.y = REC_Calorimeter.get<float>("y", i);
        cal_struct.z = REC_Calorimeter.get<float>("z", i);
        cal_struct.lu = REC_Calorimeter.get<float>("lu", i);
        cal_struct.lv = REC_Calorimeter.get<float>("lv", i);
        cal_struct.lw = REC_Calorimeter.get<float>("lw", i);
    };

    // Layer numbers to their respective calorimeter types for clarity:
    // 1 -> preshower calorimeter (PCAL)
    // 4 -> inner calorimeter (ECin)
    // 7 -> outer calorimeter (ECout)
    for (int i : map.at(pindex)) {
        if (REC_Calorimeter.get<int>("detector", i) != 7) continue;

        int layer = REC_Calorimeter.get<int>("layer", i);
        if (layer == 1) {
            populate_calorimeter_struct(output.pcal, i);
        } else if (layer == 4) {
            populate_calorimeter_struct(output.inner, i);
        } else if (layer == 7) {
            populate_calorimeter_struct(output.outer, i);
        }
    }

    return output;
}

struct DCTrackBank {
    int index = std::numeric_limits<int>::quiet_NaN();
    int pindex = std::numeric_limits<int>::quiet_NaN();
    int detector = std::numeric_limits<int>::quiet_NaN();
    int sector = std::numeric_limits<int>::quiet_NaN();
    int status = std::numeric_limits<int>::quiet_NaN();
    int q = std::numeric_limits<int>::quiet_NaN();
    float chi2 = std::numeric_limits<int>::quiet_NaN();
    int ndf = std::numeric_limits<int>::quiet_NaN();
    int hbindex = std::numeric_limits<int>::quiet_NaN();
};

inline auto read_Track_bank(const hipo::bank& REC_Track, const int pindex) -> DCTrackBank {
    auto map = load_bank_by_index(REC_Track, "pindex");
    DCTrackBank output;

    if (!map.contains(pindex)) return output;

    for (int i : map.at(pindex)) {
        if (REC_Track.get<int>("detector", i) == 6) {
            output.index = REC_Track.get<int>("index", i);
            output.pindex = REC_Track.get<int>("pindex", i);
            output.detector = REC_Track.get<int>("detector", i);
            output.sector = REC_Track.get<int>("sector", i);
            output.status = REC_Track.get<int>("status", i);
            output.q = REC_Track.get<int>("q", i);
            output.chi2 = REC_Track.get<float>("chi2", i);
            output.ndf = REC_Track.get<int>("NDF", i);
            output.hbindex = REC_Track.get<int>("hbindex", i);
        }
    }

    return output;
}

struct TrajBank {
    int pindex = std::numeric_limits<int>::quiet_NaN();
    int index = std::numeric_limits<int>::quiet_NaN();
    int detector = std::numeric_limits<int>::quiet_NaN();
    int layer = std::numeric_limits<int>::quiet_NaN();
    double x = std::numeric_limits<double>::quiet_NaN();
    double y = std::numeric_limits<double>::quiet_NaN();
    double z = std::numeric_limits<double>::quiet_NaN();
    double cx = std::numeric_limits<double>::quiet_NaN();
    double cy = std::numeric_limits<double>::quiet_NaN();
    double cz = std::numeric_limits<double>::quiet_NaN();
    double path = std::numeric_limits<double>::quiet_NaN();
    double edge = std::numeric_limits<double>::quiet_NaN();
};

struct DCTrajBank {
    TrajBank region1;
    TrajBank region2;
    TrajBank region3;
};

inline auto read_Traj_bank(const hipo::bank& REC_Traj, const int pindex) -> DCTrajBank {
    auto map = load_bank_by_index(REC_Traj, "pindex");
    DCTrajBank output;

    if (!map.contains(pindex)) return output;

    auto populate_traj_struct = [&REC_Traj](TrajBank& region, const int i) {
        region.pindex = REC_Traj.get<int>("pindex", i);
        region.index = REC_Traj.get<int>("index", i);
        region.detector = REC_Traj.get<int>("detector", i);
        region.layer = REC_Traj.get<int>("layer", i);
        region.x = REC_Traj.get<double>("x", i);
        region.y = REC_Traj.get<double>("y", i);
        region.z = REC_Traj.get<double>("z", i);
        region.cx = REC_Traj.get<double>("cx", i);
        region.cy = REC_Traj.get<double>("cy", i);
        region.cz = REC_Traj.get<double>("cz", i);
        region.path = REC_Traj.get<double>("path", i);
        region.edge = REC_Traj.get<double>("edge", i);
    };

    for (int i : map.at(pindex)) {
        if (REC_Traj.get<int>("detector", i) == 6 and REC_Traj.get<int>("layer", i) == 6)
            populate_traj_struct(output.region1, i);

        if (REC_Traj.get<int>("detector", i) == 6 and REC_Traj.get<int>("layer", i) == 18)
            populate_traj_struct(output.region2, i);

        if (REC_Traj.get<int>("detector", i) == 6 and REC_Traj.get<int>("layer", i) == 36)
            populate_traj_struct(output.region3, i);
    }

    return output;
}

}  // namespace Core
