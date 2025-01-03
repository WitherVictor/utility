#include <algorithm>
#include <charconv>
#include <concepts>
#include <random>
#include <ranges>
#include <format>
#include <type_traits>

template <std::integral Tp>
class rng {
public:
    rng(Tp begin, Tp end)
        : m_range{begin, end}
    {
        std::random_device rd{};
        std::array<Tp, std::mt19937_64::state_size> seed_data{};
        std::ranges::generate(seed_data, std::ref(rd));
        std::seed_seq seed_sequence(std::begin(seed_data), std::end(seed_data));

        m_engine = std::mt19937_64{seed_sequence};
    }

    Tp yield() { return m_range(m_engine); }
private:
    std::mt19937_64 m_engine;
    std::uniform_int_distribution<Tp> m_range;
};

template <typename Tp, typename Up>
rng(Tp, Up) -> rng<std::common_type_t<Tp, Up>>;

struct dice_data {
    dice_data(const std::vector<std::string>& dice_info) {
        std::from_chars(dice_info.at(0).data(), dice_info.at(0).data() + dice_info.at(0).size(), count);
        std::from_chars(dice_info.at(1).data(), dice_info.at(1).data() + dice_info.at(1).size(), face);
        
        if (dice_info.size() > 2) {
            std::from_chars(dice_info.at(2).data(), dice_info.at(2).data() + dice_info.at(2).size(), modifier);
        } else {
            modifier = 0;
        }
    }

    std::size_t count{};
    std::size_t face{};
    std::size_t modifier{};
};

dice_data parse_dice_info(std::string dice_info) {    
    for (auto& ch : dice_info) {
        if (ch == 'd' || ch == '+') {
            ch = ' ';
        }
    }

    return dice_info | std::views::split(' ') | std::ranges::to<std::vector<std::string>>();
}

template <typename Tp = std::size_t>
std::string roll_dice(const std::string& dice_info) {
    if (dice_info.find('d') == std::string::npos) {
        return "Invalid dice info";
    }

    auto dice_data = parse_dice_info(dice_info);
    rng generator{1uz, dice_data.face};

    std::vector<Tp> result(dice_data.count);
    std::generate_n(result.begin(), dice_data.count, [&]() {
        return generator.yield() + dice_data.modifier;
    });

    return std::format("{} : {}", dice_info, result);
}