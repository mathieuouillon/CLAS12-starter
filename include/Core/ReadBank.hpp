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
    if (from_bank.getRows() > 0) {
        for (int i_from = 0; i_from < from_bank.getRows(); i_from++) {
            int iTo = from_bank.get<float>(idx.data(), i_from);
            if (!map.contains(iTo)) map.try_emplace(iTo);
            map.at(iTo).emplace_back(i_from);
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

}  // namespace Core
