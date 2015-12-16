package com.example.pavel.stickysapphire;

import android.util.Log;

import org.wrenchrough.Updater;

public class StickyUpdater extends Updater {

    public StickyUpdater() {
        super();
    }

    @Override
    public void update(int width, int height, String data) {
        Log.d(this.getClass().getName(), "Update " + data);
    }

}
