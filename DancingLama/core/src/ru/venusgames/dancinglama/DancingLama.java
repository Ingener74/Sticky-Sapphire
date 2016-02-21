package ru.venusgames.dancinglama;

import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Pixmap;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

public class DancingLama extends ApplicationAdapter {
    private SpriteBatch batch;
    private Texture img;
    private Texture videoTexture;
    private Texture badLogicGames;

    @Override
    public void create() {

        batch = new SpriteBatch();
        img = new Texture("no_camera.png");
        badLogicGames = new Texture("badlogic.jpg");

        Gdx.app.postRunnable(new Runnable() {
            @Override
            public void run() {
                byte[] bytes = {
                        0, (byte) 255, 0, 0, (byte) 255, 0, 0, (byte) 255, 0, 0, (byte) 255, 0,
                        0, (byte) 255, 0, 0, (byte) 255, 0, 0, (byte) 255, 0, 0, (byte) 255, 0,
                        0, (byte) 255, 0, 0, (byte) 255, 0, 0, (byte) 255, 0, 0, (byte) 255, 0,
                        0, (byte) 255, 0, 0, (byte) 255, 0, 0, (byte) 255, 0, 0, (byte) 255, 0,
                };
                videoTexture = new Texture(128, 128, Pixmap.Format.RGBA8888);
            }
        });

    }

    @Override
    public void render() {
        Gdx.gl.glClearColor(1, 0, 0, 1);
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

        batch.begin();
        batch.draw(img, 300, 300/*, Gdx.graphics.getWidth(), Gdx.graphics.getHeight()*/);
        batch.draw(badLogicGames, 30, 30);
        batch.draw(videoTexture, 0, 0);
        batch.end();
    }
}
