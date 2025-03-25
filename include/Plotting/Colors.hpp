#pragma once

// ROOT includes
#include <TColor.h>

namespace Plotting {
struct Color {
    const static inline int16_t kBlue = static_cast<int16_t>(TColor::GetColor("#0C5DA5"));
    const static inline int16_t kRed = static_cast<int16_t>(TColor::GetColor("#FF2C00"));
    const static inline int16_t kViolet = static_cast<int16_t>(TColor::GetColor("#964a8b"));
    const static inline int16_t kGreen = static_cast<int16_t>(TColor::GetColor("#006F29"));
    const static inline int16_t kOrange = static_cast<int16_t>(TColor::GetColor("#ffa600"));
    const static inline int16_t kGrey = static_cast<int16_t>(TColor::GetColor("#787878"));
    const static inline int16_t kBlack = static_cast<int16_t>(TColor::GetColor("#121415"));
    const static inline int16_t kMarron = static_cast<int16_t>(TColor::GetColor("#9c5e3d"));
    const static inline int16_t kDarkBlue = static_cast<int16_t>(TColor::GetColor("#395892"));
    const static inline int16_t kLightGreen = static_cast<int16_t>(TColor::GetColor("#66a87e"));
    const static inline int16_t kPink = static_cast<int16_t>(TColor::GetColor("#ee3377"));
    const static inline int16_t kDarkPink = static_cast<int16_t>(TColor::GetColor("#8e1e47"));
    const static inline int16_t kPaul = static_cast<int16_t>(TColor::GetColor("#009988"));
    const static inline int16_t kDarkPaul = static_cast<int16_t>(TColor::GetColor("#004c44"));

    const static inline int16_t kDarkRed = static_cast<int16_t>(TColor::GetColor("#a21025"));
    const static inline int16_t kViolet2 = static_cast<int16_t>(TColor::GetColor("#7a49a5"));
    const static inline int16_t kBlue2 = static_cast<int16_t>(TColor::GetColor("#4974a5"));
    const static inline int16_t kGreen2 = static_cast<int16_t>(TColor::GetColor("#3a7512"));
};
}  // namespace Plotting