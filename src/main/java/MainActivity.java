// Copyright 2023 Daniel C - https://github.com/petabyt/fujiapp
package dev.danielc.us;

import android.content.Context;
import android.os.Bundle;
import android.view.MenuItem;

import androidx.appcompat.app.AppCompatActivity;

import libui.LibUI;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("app");
    }

	public native static void StartUI(Context ctx);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        LibUI.buttonBackgroundResource = R.drawable.grey_button;
        StartUI(this);
    }

   @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        return LibUI.handleOptions(item, false);
    }
}
