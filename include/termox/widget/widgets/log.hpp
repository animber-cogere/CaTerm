#ifndef CATERM_WIDGET_WIDGETS_LOG_HPP
#define CATERM_WIDGET_WIDGETS_LOG_HPP
#include <memory>

#include <caterm/painter/glyph_string.hpp>
#include <caterm/system/key.hpp>
#include <caterm/widget/widgets/text_view.hpp>
#include <caterm/widget/widgets/textbox.hpp>

namespace ox {

/// A scrollable list of logged messages.
/** Received messages are posted at the bottom of the Log. */
class Log : public Textbox {
   public:
    struct Parameters {};

   public:
    explicit Log(Parameters = {});

   public:
    void post_message(Glyph_string message);

   protected:
    auto key_press_event(Key k) -> bool override;

   private:
    using Text_view::append;
    using Text_view::erase;
    using Text_view::insert;
    using Text_view::pop_back;
    using Text_view::set_text;
};

/// Helper function to create a Log instance.
[[nodiscard]] inline auto log(Log::Parameters parameters = {})
    -> std::unique_ptr<Log>;

}  // namespace ox
#endif  // CATERM_WIDGET_WIDGETS_LOG_HPP
