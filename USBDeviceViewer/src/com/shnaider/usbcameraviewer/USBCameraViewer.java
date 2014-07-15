package com.shnaider.usbcameraviewer;

import android.app.Activity;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.widget.ImageView;

public class USBCameraViewer extends Activity {

	static {
		System.loadLibrary("UsbCameraViewer");
	}

	private native boolean startUsbCameraViewer();

	private native void stopUsbCameraViewer();

	ImageView _previewImage = null;

	void drawBitmap(final Bitmap bitmap) {
		_previewImage.post(new Runnable() {

			@Override
			public void run() {
				_previewImage.setImageBitmap(bitmap);
			}
		});
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		_previewImage = (ImageView) findViewById(R.id.PreviewImage);
	}

	@Override
	public void onStart() {
		super.onStart();
	}

	@Override
	public void onRestart() {
		super.onRestart();
	}

	@Override
	public void onResume() {
		super.onResume();
		startUsbCameraViewer();
	}

	@Override
	public void onPause() {
		super.onPause();
		stopUsbCameraViewer();
	}

	@Override
	public void onStop() {
		super.onStop();
	}

	@Override
	public void onDestroy() {
		super.onDestroy();
	}
}
