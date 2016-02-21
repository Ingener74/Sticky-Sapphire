package com.example.pavel.stickysapphire;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

import org.wrenchrough.Capture;
import org.wrenchrough.Updater;

public class StickySapphireActivity extends AppCompatActivity {

    private Capture capture;
    private Updater updater;
    private StickySapphireGlSurfaceView glView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        glView = new StickySapphireGlSurfaceView(this);
        setContentView(glView);

        updater = new StickyUpdater();
        capture = new Capture(100, 100, 0, updater);
    }

    static {
        System.loadLibrary("WrenchRough");
    }
}
