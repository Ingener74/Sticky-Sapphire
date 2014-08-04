package com.shnaider.usbcameraviewer;

import java.util.HashMap;
import java.util.Iterator;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Bitmap;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbManager;
import android.os.Bundle;
import android.util.Log;
import android.widget.ImageView;

public class USBCameraViewer extends Activity {

	private static String TAG = USBCameraViewer.class.getName();

	static {
		System.loadLibrary("UsbCameraViewer");
	}

	private native boolean startUsbCameraViewer();

	private native void stopUsbCameraViewer();

	ImageView _previewImage = null;

	private static final String ACTION_USB_PERMISSION = "com.android.example.USB_PERMISSION";
	private final BroadcastReceiver mUsbReceiver = new BroadcastReceiver() {

		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();
			if (ACTION_USB_PERMISSION.equals(action)) {
				synchronized (this) {
					UsbDevice device = (UsbDevice) intent
							.getParcelableExtra(UsbManager.EXTRA_DEVICE);

					if (intent.getBooleanExtra(
							UsbManager.EXTRA_PERMISSION_GRANTED, false)) {
						if (device != null) {

							startUsbCameraViewer();

						}
					} else {
						Log.d(TAG, "permission denied for device " + device);
					}
				}
			}
		}
	};

	private PendingIntent mPermissionIntent;

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

		UsbManager manager = (UsbManager) getSystemService(Context.USB_SERVICE);

		mPermissionIntent = PendingIntent.getBroadcast(this, 0, new Intent(
				ACTION_USB_PERMISSION), 0);
		IntentFilter filter = new IntentFilter(ACTION_USB_PERMISSION);
		registerReceiver(mUsbReceiver, filter);

		HashMap<String, UsbDevice> deviceList = manager.getDeviceList();
		Iterator<UsbDevice> deviceIterator = deviceList.values().iterator();
		while (deviceIterator.hasNext()) {
			UsbDevice device = deviceIterator.next();

			// USB\VID_046D&PID_082D&REV_0011&MI_02

			if (device.getVendorId() == 0x046D
					&& device.getProductId() == 0x082D) {

				manager.requestPermission(device, mPermissionIntent);

				return;
			}
		}

		AlertDialog.Builder builder = new AlertDialog.Builder(this);
		builder.setTitle("Error").setMessage("can't find usb device")
				.setCancelable(false)
				.setNeutralButton("OK", new OnClickListener() {

					@Override
					public void onClick(DialogInterface dialog, int which) {
						finish();
					}
				});
		
		AlertDialog alert = builder.create();
		alert.show();
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
