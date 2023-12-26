// Copyright 2023 Daniel C - https://github.com/petabyt/fujiapp
package dev.danielc.us;

import android.Manifest;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.net.ConnectivityManager;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkRequest;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import libui.LibUI;

public class MainActivity extends AppCompatActivity {
    static {
        System.loadLibrary("app");
    }

	public native static void StartUI(Context ctx);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        LibUI.buttonBackgroundResource = R.drawable.grey_button;

        StartUI(this);
    }

   @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        return LibUI.handleOptions(item, false);
    }
}
