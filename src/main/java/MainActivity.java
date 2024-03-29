// Copyright 2023 Daniel C - https://github.com/petabyt/fujiapp
package dev.danielc.us;

import android.content.Context;
import android.os.Bundle;
import android.view.MenuItem;
import android.app.Activity;

import java.io.InputStream;

import libui.LibUI;

public class MainActivity extends Activity {
    static {
        System.loadLibrary("app");
    }

	public native static void StartUI(Context ctx, String constitution);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        try {
            InputStream stream = getAssets().open("const.txt");
            int size = stream.available();
            byte[] buffer = new byte[size];
            stream.read(buffer);
            stream.close();

            StartUI(this, new String(buffer));
        } catch (Exception e) {

        }
    }
}
