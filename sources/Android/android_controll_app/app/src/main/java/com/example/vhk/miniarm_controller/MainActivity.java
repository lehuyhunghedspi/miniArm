package com.example.vhk.miniarm_controller;

import android.app.Activity;
import android.content.Intent;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import app.akexorcist.bluetotohspp.library.BluetoothSPP;
import app.akexorcist.bluetotohspp.library.BluetoothState;
import app.akexorcist.bluetotohspp.library.DeviceList;

public class MainActivity extends AppCompatActivity {
    BluetoothSPP bluetooth;
    Button connectBtn;

    Button resetPosBtn;

    Button turnLeftBtn;
    Button turnRightBtn;

    Button upShoulderBtn;
    Button downShoulderBtn;

    Button upElblowBtn;
    Button downElblowBtn;

    Button openGripperBtn;
    Button closeGrippetBtn;


    Button stopBtn;

    Button saveBtn;
    Button runScriptBtn;
    Button startNewRecordBtn;

    final String turnLeft = "3";
    final String turnRight = "4";

    final String openGripper = "8";
    final String closeGripper = "7";

    final String upShoulder = "5";
    final String downShoulder = "6";

    final String upElblow = "1";
    final String downElblow = "2";

    final String stopArm = "0";

    final String resetState = "9";

    final String saveState = "s";
    final String runScripts = "r";
    final String startNewRecord = "n";

    final static int delay_time = 10;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        bluetooth = new BluetoothSPP(this);
        connectBtn = (Button) findViewById(R.id.connectBtn);

        turnLeftBtn = (Button) findViewById(R.id.turnLeftBtn);
        turnRightBtn = (Button) findViewById(R.id.turnRightBtn);

        upShoulderBtn = (Button) findViewById(R.id.upShoulderBtn);
        downShoulderBtn = (Button)findViewById(R.id.downShoulderBtn);

        upElblowBtn = (Button)findViewById(R.id.upElblowBtn);
        downElblowBtn = (Button)findViewById(R.id.downElblowBtn);

        openGripperBtn = (Button)findViewById(R.id.openGripperBtn);
        closeGrippetBtn = (Button)findViewById(R.id.closeGripperBtn);

        resetPosBtn = (Button)findViewById(R.id.resetPosBtn);


        stopBtn = (Button)findViewById(R.id.stopBtn);

        saveBtn = (Button) findViewById(R.id.saveBtn);
        runScriptBtn = (Button)findViewById(R.id.runScriptBtn);
        startNewRecordBtn = (Button) findViewById(R.id.startRecordBtn);

        if (!bluetooth.isBluetoothAvailable()) {
            Toast.makeText(getApplicationContext(), "Bluetooth is not available", Toast.LENGTH_SHORT).show();
            finish();
        }

        bluetooth.setBluetoothConnectionListener(new BluetoothSPP.BluetoothConnectionListener() {
            public void onDeviceConnected(String name, String address) {
                connectBtn.setText("Connected to " + name);
            }

            public void onDeviceDisconnected() {
                connectBtn.setText("Connection lost");
            }

            public void onDeviceConnectionFailed() {
                connectBtn.setText("Unable to connect");
            }
        });



        connectBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (bluetooth.getServiceState() == BluetoothState.STATE_CONNECTED) {
                    bluetooth.disconnect();
                } else {
                    Intent intent = new Intent(getApplicationContext(), DeviceList.class);
                    startActivityForResult(intent, BluetoothState.REQUEST_CONNECT_DEVICE);
                }
            }
        });

        startNewRecordBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                bluetooth.send("n",true);
                Toast.makeText(getApplicationContext(),"Let's make new record",Toast.LENGTH_SHORT).show();
            }
        });
        stopBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                bluetooth.send(stopArm,true);
            }
        });

        saveBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                bluetooth.send("s",true);
                Toast.makeText(getApplicationContext(),"Saved",Toast.LENGTH_SHORT).show();
            }
        });

        runScriptBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                bluetooth.send("r",true);
            }
        });

        turnLeftBtn.setOnTouchListener(new View.OnTouchListener()
        {

            private Handler mHandler;

            @Override public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        if (mHandler != null) return true;
                        mHandler = new Handler();
                        mHandler.postDelayed(mAction, delay_time);
                        break;
                    case MotionEvent.ACTION_UP:
                        if (mHandler == null) return true;
                        mHandler.removeCallbacks(mAction);
                        mHandler = null;
                        break;
                }
                return false;
            }

            Runnable mAction = new Runnable() {
                @Override public void run() {
                    bluetooth.send(turnLeft,true);
                    mHandler.postDelayed(this, delay_time);
                }
            };
        });

        turnRightBtn.setOnTouchListener(new View.OnTouchListener()
        {

            private Handler mHandler;

            @Override public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        if (mHandler != null) return true;
                        mHandler = new Handler();
                        mHandler.postDelayed(mAction, delay_time);
                        break;
                    case MotionEvent.ACTION_UP:
                        if (mHandler == null) return true;
                        mHandler.removeCallbacks(mAction);
                        mHandler = null;
                        break;
                }
                return false;
            }

            Runnable mAction = new Runnable() {
                @Override public void run() {
                    bluetooth.send(turnRight,true);
                    mHandler.postDelayed(this, delay_time);
                }
            };
        });

        upShoulderBtn.setOnTouchListener(new View.OnTouchListener()
        {

            private Handler mHandler;

            @Override public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        if (mHandler != null) return true;
                        mHandler = new Handler();
                        mHandler.postDelayed(mAction, delay_time);
                        break;
                    case MotionEvent.ACTION_UP:
                        if (mHandler == null) return true;
                        mHandler.removeCallbacks(mAction);
                        mHandler = null;
                        break;
                }
                return false;
            }

            Runnable mAction = new Runnable() {
                @Override public void run() {
                    bluetooth.send(upShoulder,true);
                    mHandler.postDelayed(this, delay_time);
                }
            };
        });

        downShoulderBtn.setOnTouchListener(new View.OnTouchListener()
        {

            private Handler mHandler;

            @Override public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        if (mHandler != null) return true;
                        mHandler = new Handler();
                        mHandler.postDelayed(mAction, delay_time);
                        break;
                    case MotionEvent.ACTION_UP:
                        if (mHandler == null) return true;
                        mHandler.removeCallbacks(mAction);
                        mHandler = null;
                        break;
                }
                return false;
            }

            Runnable mAction = new Runnable() {
                @Override public void run() {
                    bluetooth.send(downShoulder,true);
                    mHandler.postDelayed(this, delay_time);
                }
            };
        });

        upElblowBtn.setOnTouchListener(new View.OnTouchListener()
        {

            private Handler mHandler;

            @Override public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        if (mHandler != null) return true;
                        mHandler = new Handler();
                        mHandler.postDelayed(mAction, delay_time);
                        break;
                    case MotionEvent.ACTION_UP:
                        if (mHandler == null) return true;
                        mHandler.removeCallbacks(mAction);
                        mHandler = null;
                        break;
                }
                return false;
            }

            Runnable mAction = new Runnable() {
                @Override public void run() {
                    bluetooth.send(upElblow,true);
                    mHandler.postDelayed(this, delay_time);
                }
            };
        });

        downElblowBtn.setOnTouchListener(new View.OnTouchListener()
        {

            private Handler mHandler;

            @Override public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        if (mHandler != null) return true;
                        mHandler = new Handler();
                        mHandler.postDelayed(mAction, delay_time);
                        break;
                    case MotionEvent.ACTION_UP:
                        if (mHandler == null) return true;
                        mHandler.removeCallbacks(mAction);
                        mHandler = null;
                        break;
                }
                return false;
            }

            Runnable mAction = new Runnable() {
                @Override public void run() {
                    bluetooth.send(downElblow,true);
                    mHandler.postDelayed(this, delay_time);
                }
            };
        });

        openGripperBtn.setOnTouchListener(new View.OnTouchListener()
        {

            private Handler mHandler;

            @Override public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        if (mHandler != null) return true;
                        mHandler = new Handler();
                        mHandler.postDelayed(mAction, delay_time);
                        break;
                    case MotionEvent.ACTION_UP:
                        if (mHandler == null) return true;
                        mHandler.removeCallbacks(mAction);
                        mHandler = null;
                        break;
                }
                return false;
            }

            Runnable mAction = new Runnable() {
                @Override public void run() {
                    bluetooth.send(openGripper,true);
                    mHandler.postDelayed(this, delay_time);
                }
            };
        });

        closeGrippetBtn.setOnTouchListener(new View.OnTouchListener()
        {

            private Handler mHandler;

            @Override public boolean onTouch(View v, MotionEvent event) {
                switch(event.getAction()) {
                    case MotionEvent.ACTION_DOWN:
                        if (mHandler != null) return true;
                        mHandler = new Handler();
                        mHandler.postDelayed(mAction, delay_time);
                        break;
                    case MotionEvent.ACTION_UP:
                        if (mHandler == null) return true;
                        mHandler.removeCallbacks(mAction);
                        mHandler = null;
                        break;
                }
                return false;
            }

            Runnable mAction = new Runnable() {
                @Override public void run() {
                    bluetooth.send(closeGripper,true);
                    mHandler.postDelayed(this, delay_time);
                }
            };
        });

        resetPosBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                bluetooth.send(resetState,true);
            }
        });
    }

    public void onStart() {
        super.onStart();
        if (!bluetooth.isBluetoothEnabled()) {
            bluetooth.enable();
        } else {
            if (!bluetooth.isServiceAvailable()) {
                bluetooth.setupService();
                bluetooth.startService(BluetoothState.DEVICE_OTHER);
            }
        }
    }


    public void onDestroy() {
        super.onDestroy();
        bluetooth.stopService();
    }

    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == BluetoothState.REQUEST_CONNECT_DEVICE) {
            if (resultCode == Activity.RESULT_OK)
                bluetooth.connect(data);
        } else if (requestCode == BluetoothState.REQUEST_ENABLE_BT) {
            if (resultCode == Activity.RESULT_OK) {
                bluetooth.setupService();
            } else {
                Toast.makeText(getApplicationContext()
                        , "Bluetooth was not enabled."
                        , Toast.LENGTH_SHORT).show();
                finish();
            }
        }
    }

}
