package com.example.pavel.stickysapphire;

import android.opengl.GLSurfaceView;

/**
 * Created by pavel on 21.02.16.
 */
public class StickySapphireGlSurfaceView extends GLSurfaceView {
    private final StickySapphireRenderer renderer;

    public StickySapphireGlSurfaceView(StickySapphireActivity activity) {
        super(activity);
        setEGLContextClientVersion(2);

        renderer = new StickySapphireRenderer();
        setRenderer(renderer);
    }
}
