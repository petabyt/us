#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myjni.h"

#include <ui.h>
#include <fw.h>

#include "json.h"

void uiLabelSetTextSize(uiLabel *l, float size);

static uiScroll *get_articles(const char *constitution) {
    struct Parse p;
    uiLabel *lbl;

    uiScroll *scroll = uiNewScroll();

    uiBox *box = uiNewVerticalBox();
    uiBoxSetPadded(box, 1);

    uiBoxAppend(scroll, uiControl(box), 0);

    lbl = uiNewLabel("We the people");
    uiLabelSetTextSize(lbl, 25.0);
    uiBoxAppend(box, uiControl(lbl), 0);

    json_get(&p, constitution, "['preamble']");
    char *buf = json_fixup_string(&p);
    uiBoxAppend(box, uiControl(uiNewLabel(buf + 14)), 0);
    free(buf);

    int lengths[] = {10, 4, 3, 4, 1, 1};
    for (int s = 0; s < 6; s++) {
        for (int i = 0; i < lengths[s]; i++) {
            char req[64];
            snprintf(req, sizeof(req), "['articles'][%d][%d]", s, i);

            json_get(&p, constitution, req);

            buf = json_fixup_string(&p);
            uiBoxAppend(box, uiControl(uiNewLabel(buf)), 0);
            free(buf);
        }

        uiBoxAppend(box, uiControl(uiNewVerticalSeparator()), 0);
    }

    lbl = uiNewLabel("Signatories");
    uiLabelSetTextSize(lbl, 20.0);
    uiBoxAppend(box, uiControl(lbl), 0);

    json_get(&p, constitution, "['signatories']");
    buf = json_fixup_string(&p);
    uiBoxAppend(box, uiControl(uiNewLabel(buf)), 0);
    free(buf);

    return scroll;
}

static uiScroll *get_amendments(const char *constitution) {
    struct Parse p;
    uiScroll *scroll = uiNewScroll();

    uiBox *box = uiNewVerticalBox();
    uiBoxSetPadded(box, 1);

    uiBoxAppend(scroll, uiControl(box), 0);

    for (int i = 0; i < 27; i++) {
        char req[64];
        snprintf(req, sizeof(req), "Amendment #%d", i + 1);
        uiLabel *lbl = uiNewLabel(req);
        uiLabelSetTextSize(lbl, 20.0);
        uiBoxAppend(box, uiControl(lbl), 0);

        snprintf(req, sizeof(req), "['amendments'][%d]", i);

        json_get(&p, constitution, req);

        char *buf = json_fixup_string(&p);
        uiBoxAppend(box, uiControl(uiNewLabel(buf)), 0);
        free(buf);

        uiBoxAppend(box, uiControl(uiNewVerticalSeparator()), 0);
    }

    return scroll;
}

static uiTab *get_app(const char *constitution) {
    uiLabel *lbl;
    uiBox *box;
    uiScroll *scroll;

    uiTab *tab = uiNewTab();

    uiTabAppend(tab, "Articles", uiControl(get_articles(constitution)));
    uiTabAppend(tab, "Amendments", uiControl(get_amendments(constitution)));

    uiBox *about = uiNewVerticalBox();
    uiBoxSetPadded(about, 1);
    uiBoxAppend(about, uiControl(uiNewLabel("Created with LibUI")), 0);
    uiBoxAppend(about, uiControl(uiNewLabel("Compiled for all platforms, this APK is 666kb."
                                            " Download size for single arch is 516kb.")), 0);
    uiBoxAppend(about, uiControl(uiNewLabel("All the UI you see here was created in C, and the exact"
                                            " same code can be run on Windows, Linux, and MacOS.")), 0);
    uiBoxAppend(about, uiControl(uiNewButton("That's neat")), 0); // toast something ;)


    uiTabAppend(tab, "About", uiControl(about));

    return tab;
}

JNI_FUNC(void, StartUI)(JNIEnv *env, jobject thiz, jobject ctx, jstring string) {
	if (uiAndroidInit(env, ctx)) abort();
    const char *str = (*env)->GetStringUTFChars(env, string, 0);
	uiAndroidSetContent(uiControl(get_app(str)));
}
