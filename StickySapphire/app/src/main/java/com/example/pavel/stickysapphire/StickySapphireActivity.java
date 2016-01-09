package com.example.pavel.stickysapphire;

import android.os.SystemClock;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import org.wrenchrough.Capture;
import org.wrenchrough.Updater;

public class StickySapphireActivity extends AppCompatActivity {

    private Capture capture;
    private Updater updater;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sticky_sapphire);

        updater = new StickyUpdater();
        capture = new Capture(100, 100, 0, updater);
    }

    static {
        System.loadLibrary("WrenchRough");
    }
}
