#include "args.h"
#include "argh.h"


class CmdArgs::Impl {
public:
    void Parse(const char* const* const argv) noexcept {
        cmdl_.parse(argv);
    }

    std::size_t GetWidth() const noexcept {
        std::size_t width {0};
        cmdl_(width_opt_.data()) >> width;
        return width;
    }

    std::size_t GetHeight() const noexcept {
        std::size_t height {0};
        cmdl_(height_opt_.data()) >> height;
        return height;
    }

private:
    static constexpr std::string_view width_opt_ {"x"};

    static constexpr std::string_view height_opt_ {"y"};

    argh::parser cmdl_;
};

CmdArgs::CmdArgs() noexcept : impl_ {std::make_unique<Impl>()} {}

CmdArgs::~CmdArgs() noexcept = default;

void CmdArgs::Parse(const char* const* const argv) noexcept {
    impl_->Parse(argv);
}

std::size_t CmdArgs::GetWidth() const noexcept {
    return impl_->GetWidth();
}

std::size_t CmdArgs::GetHeight() const noexcept {
    return impl_->GetHeight();
}