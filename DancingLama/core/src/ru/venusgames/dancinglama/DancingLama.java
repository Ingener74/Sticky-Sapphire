package ru.venusgames.dancinglama;

import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Color;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.Pixmap;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

public class DancingLama extends ApplicationAdapter {
    SpriteBatch batch;
    Texture img;

    private Texture videoTexture;
    private SpriteBatch videoBatch;

    @Override
    public void create() {
        batch = new SpriteBatch();
        img = new Texture("no_camera.png");

        videoBatch = new SpriteBatch();
        videoTexture = new Texture(128, 128, Pixmap.Format.RGBA8888);
        videoTexture.getTextureData().consumePixmap().setColor(new Color(0.1f, 1.0f, 0.1f, 1.0f));
        videoTexture.getTextureData().consumePixmap().fillCircle(0, 0, 100);
    }

    @Override
    public void render() {
        Gdx.gl.glClearColor(1, 0, 0, 1);
        Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);

        batch.begin();
        batch.draw(img, 300, 300/*, Gdx.graphics.getWidth(), Gdx.graphics.getHeight()*/);
        batch.end();

        videoBatch.begin();
        videoBatch.draw(videoTexture, 0, 0);
        videoBatch.end();
    }
}
