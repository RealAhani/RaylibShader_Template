#pragma once
namespace
{
namespace RA_Global
{
// all of path should start without / e.g= resources/...
inline static constexpr str_v const texturePath = "resource/textures/";
inline static constexpr str_v const fontPath    = "resource/fonts/";
inline static constexpr str_v const shadersPath = "resource/shaders/glsl";

enum class EFileType : u8
{
    Texture = 0,
    Font,
    Shader
};
constexpr Color const grey = Color {37, 37, 37, 255};

/*
 *@Goal: return the path to file based on fileType
 *@Note: put the file in
 *{currentProject}/resources/assets/resource/{fileType-folderName}/fileType
 */
[[nodiscard]] [[maybe_unused]]
auto pathToFile(str_v const fileName, EFileType const fileType) -> str
{
    str path;
#if defined(PLATFORM_DESKTOP)  // finding abs path on deskto
    str const root = GetApplicationDirectory();
    path.append(root);
#endif
    switch (fileType)
    {
        case EFileType::Font:
        {
            path.append(RA_Global::fontPath);
            break;
        }
        case EFileType::Texture:
        {
            path.append(RA_Global::texturePath);
            break;
        }
        case EFileType::Shader:
        {
            // the 2 is the glsl define size
            path.append(RA_Global::shadersPath);
            path.append(TextFormat("%i/", GLSL_VERSION));
            break;
        }
    }
    path.append(fileName);
    return path;
}

}  // namespace RA_Global
namespace RA_Font
{
/*
 * @Goat: draw text as a sdf mode
 */
[[nodiscard]] [[maybe_unused]]
auto initFont(str_v const fontFileName, i32 const fontSize, TextureFilter const filterFlag)
    -> std::pair<Font, f32>
{
    auto font = LoadFontEx(RA_Global::pathToFile(fontFileName, RA_Global::EFileType::Font)
                               .c_str(),
                           fontSize,
                           nullptr,
                           0);
    GenTextureMipmaps(&font.texture);
    SetTextureFilter(font.texture, filterFlag);
    return std::pair {font, cast(f32, font.baseSize)};
}
}  // namespace RA_Font

namespace RA_Util
{

class GRandom
{
public:

    GRandom()  = delete;
    ~GRandom() = default;
    explicit GRandom(f32 const min, f32 const max) noexcept : m_randDistro {min, max}
    {
    }

    [[nodiscard]] [[maybe_unused]]
    auto getRandom() const noexcept -> f32
    {
        return const_cast<GRandom &>(*this).getRandom();
    }

    [[nodiscard]] [[maybe_unused]]
    auto getRandom() noexcept -> f32
    {
        return m_randDistro(rand32);
    }

private:

    [[nodiscard]] [[maybe_unused]]
    static auto initRandWithSeed() noexcept -> std::mt19937 &
    {
        std::random_device  rd {};
        std::seed_seq       seed {cast(std::mt19937::result_type,
                                 std::chrono::steady_clock::now().time_since_epoch().count()),
                            cast(std::mt19937::result_type, rd())};
        static std::mt19937 rand {seed};
        return rand;
    }

    std::uniform_real_distribution<f32> m_randDistro;
    inline static std::mt19937          rand32 {initRandWithSeed()};
};
}  // namespace RA_Util


}  // namespace