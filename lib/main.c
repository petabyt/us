#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myjni.h"

#include <ui.h>
#include "ui_android.h"

#include "json.h"
#include "const.h"

JNI_FUNC(void, StartUI)(JNIEnv *env, jobject thiz, jobject ctx) {
	uiAndroidInit(env, ctx);

	char *data = (char *)malloc(const_txt_len + 1);
	memcpy(data, const_txt, const_txt_len);

	//uiScroll *s = uiNewScroll();

	uiTab *tab = uiNewTab();

	uiBox *box = uiNewVerticalBox();
	uiBoxSetPadded(box, 1);

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

	json_get(&p, data, "['signatories']");
	char *buf = json_fixup_string(&p);
	uiBoxAppend(box, uiControl(uiNewLabel(buf)), 0);
	free(buf);

	uiTabAppend(tab, "Articles", uiControl(box));

	box = uiNewVerticalBox();
	uiBoxSetPadded(box, 1);
	for (int i = 0; i < 27; i++) {
		char req[64];

		snprintf(req, sizeof(req), "AMENDMENT #%d", i + 1);
		uiBoxAppend(box, uiControl(uiNewLabel(req)), 0);
		
		snprintf(req, sizeof(req), "['amendments'][%d]", i);

		json_get(&p, data, req);

		char *buf = json_fixup_string(&p);
		uiBoxAppend(box, uiControl(uiNewLabel(buf)), 0);
		free(buf);
	}

	uiTabAppend(tab, "Ammendments", uiControl(box));

	//uiBoxAppend(frame, uiControl(tab), 0);

	//uiBoxAppend((uiBox *)s, uiControl(box), 0);
	uiAndroidSetContent(uiControl(tab));
}
