#include <jscbind/jscbind.h>
#include <webcbind/webcbind.h>

jb_Any button_cb(const jb_Array *args, const jb_Any *data) {
    jb_Object params = jb_Object_from_val(data);
    jb_Any ctx = jb_Object_get(&params, "context");
    jb_Any os = jb_Object_get(&params, "os");
    AudioDestinationNode dest = BaseAudioContext_destination(&ctx);
    AudioNode_connect0(&os, &dest);
    AudioScheduledSourceNode_start1(&os, 0.0);
    return ANY_JB(jb_Undefined_value());
}

int main() {
    emlite_init_handle_table();
    AudioContext context = AudioContext_new0();
    OscillatorNode oscillator = OscillatorNode_new0(&context);
    OscillatorType t = OscillatorType_triangle();
    OscillatorNode_set_type(&oscillator, &t);
    AudioParam param = OscillatorNode_frequency(&oscillator);
    AudioParam_set_value(&param, 261.63); // Middle C

    Window win            = window();
    Document document     = Window_document(&win);
    HTMLCollection bodies = Document_getElementsByTagName(
        &document, &JSSTR("body")
    );
    Element body   = HTMLCollection_item(&bodies, 0);
    Element button = Document_createElement0(
        &document, &JSSTR("BUTTON")
    );
    Node_set_textContent(
        &button, &JSSTR("Play")
    );
    Node_appendChild(&body, &button);

    jb_Object params = jb_Object_new();
    jb_Object_set(&params, "context", &context);
    jb_Object_set(&params, "os", &oscillator);

    jb_Function btn_cb = jb_Function_from(button_cb, &params);

    EventTarget_addEventListener0(
        &button, &JSSTR("click"), &btn_cb
    );
    return 0;
}
