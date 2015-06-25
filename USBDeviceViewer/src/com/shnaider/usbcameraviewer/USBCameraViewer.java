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
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbManager;
import android.opengl.GLES20;
import android.opengl.GLUtils;
import android.os.Bundle;
import android.util.Log;
import android.widget.ImageView;

public class USBCameraViewer extends Activity {

	private static String TAG = USBCameraViewer.class.getName();

	static {
		System.loadLibrary("UsbCameraViewer");
	}

	private native boolean startUsbCameraViewer(int vid, int pid, int fd);

	private native void stopUsbCameraViewer();

	ImageView previewImage = null;

	UsbDeviceConnection connection = null;

	private static final String ACTION_USB_PERMISSION = "com.android.example.USB_PERMISSION";
	private final BroadcastReceiver usbReceiver = new BroadcastReceiver() {

		public void onReceive(Context context, Intent intent) {
			
			String action = intent.getAction();
			
			if (!ACTION_USB_PERMISSION.equals(action)) {
				Log.d(TAG, "action is not usb permission");
				return;
			}
			
			synchronized (this) {
				UsbDevice device = (UsbDevice) intent.getParcelableExtra(UsbManager.EXTRA_DEVICE);
				
				if (!intent.getBooleanExtra(UsbManager.EXTRA_PERMISSION_GRANTED, false)) {
					Log.d(TAG, "permission denied for device " + device);
					return;
				}
				if (device == null) {
					Log.d(TAG, "device is null");
					return;
				}
				
				Log.i(TAG, "dev " + device.getVendorId() + ", "
						+ device.getProductId());
				
				connection = ((UsbManager) context
						.getSystemService(Context.USB_SERVICE))
						.openDevice(device);
				
				if(connection == null){
					Log.d(TAG, "connection is null");
					return;
				}
				
				startUsbCameraViewer(device.getVendorId(),
						device.getProductId(),
						connection.getFileDescriptor());
			}
		}
	};

	private PendingIntent permissionIntent = null;

	void drawBitmap(final Bitmap bitmap) {
		previewImage.post(new Runnable() {

			@Override
			public void run() {
				previewImage.setImageBitmap(bitmap);
			}
		});
	}

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		
		Log.d(TAG, "onCreate");

		previewImage = (ImageView) findViewById(R.id.PreviewImage);
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

		Log.d(TAG, "onResume");

		UsbManager manager = (UsbManager) getSystemService(Context.USB_SERVICE);

		permissionIntent = PendingIntent.getBroadcast(this, 0, new Intent(ACTION_USB_PERMISSION), 0);
		
		if(permissionIntent == null){
			Log.d(TAG, "permission intent is null");
			return;
		}
		
		IntentFilter filter = new IntentFilter(ACTION_USB_PERMISSION);
		registerReceiver(usbReceiver, filter);

		HashMap<String, UsbDevice> deviceList = manager.getDeviceList();
		Iterator<UsbDevice> deviceIterator = deviceList.values().iterator();
		while (deviceIterator.hasNext()) {
			UsbDevice device = deviceIterator.next();

			// USB\VID_046D&PID_082D&REV_0011&MI_02

			if (device.getVendorId() == 0x046D && device.getProductId() == 0x082D) {
				manager.requestPermission(device, permissionIntent);

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
		
		Log.d(TAG, "onPause");
		
		stopUsbCameraViewer();
		unregisterReceiver(usbReceiver);
		if(connection == null){
			Log.d(TAG, "connection is null");
			return;
		}
		connection.close();
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
