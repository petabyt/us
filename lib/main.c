#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myjni.h"

#include <ui.h>
#include <fw.h>

#include "json.h"
#include "const.h"

void uiLabelSetTextSize(uiLabel *l, float size);

uiLabel *uiNewLabelF(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char buffer[1024];
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    return uiNewLabel(buffer);
}

JNI_FUNC(void, StartUI)(JNIEnv *env, jobject thiz, jobject ctx) {
	if (uiAndroidInit(env, ctx)) return;

	char *data = (char *)malloc(const_txt_len + 1);
	memcpy(data, const_txt, const_txt_len);

	//uiScroll *s = uiNewScroll();

	uiTab *tab = uiNewTab();

	uiBox *box = uiNewVerticalBox();
	uiBoxSetPadded(box, 1);

    uiScroll *scroll = uiNewScroll();
    uiBoxAppend(scroll, uiControl(box), 0);

	struct Parse p;
	int lengths[] = {10, 4, 3, 4, 1, 1};
	for (int s = 0; s < 6; s++) {
		for (int i = 0; i < lengths[s]; i++) {
			char req[64];
			snprintf(req, sizeof(req), "['articles'][%d][%d]", s, i);

			json_get(&p, data, req);

			char *buf = json_fixup_string(&p);
			uiBoxAppend(box, uiControl(uiNewLabel(buf)), 0);
			free(buf);
		}

		uiBoxAppend(box, uiControl(uiNewVerticalSeparator()), 0);
	}

    uiLabel *lbl = uiNewLabel("Signatories");
    uiLabelSetTextSize(lbl, 20.0);
    uiBoxAppend(box, uiControl(lbl), 0);

	json_get(&p, data, "['signatories']");
	char *buf = json_fixup_string(&p);
	uiBoxAppend(box, uiControl(uiNewLabel(buf)), 0);
	free(buf);

	uiTabAppend(tab, "Articles", uiControl(scroll));

	box = uiNewVerticalBox();
	uiBoxSetPadded(box, 1);

    scroll = uiNewScroll();
    uiBoxAppend(scroll, uiControl(box), 0);

	for (int i = 0; i < 27; i++) {
        char req[64];
        uiLabel *lbl = uiNewLabelF("Amendment #%d", i + 1);
        uiLabelSetTextSize(lbl, 20.0);
		uiBoxAppend(box, uiControl(lbl), 0);
		
		snprintf(req, sizeof(req), "['amendments'][%d]", i);

		json_get(&p, data, req);

		buf = json_fixup_string(&p);
		uiBoxAppend(box, uiControl(uiNewLabel(buf)), 0);
		free(buf);

        uiBoxAppend(box, uiControl(uiNewVerticalSeparator()), 0);
	}

	uiTabAppend(tab, "Amendments", uiControl(scroll));

	uiAndroidSetContent(uiControl(tab));
}
