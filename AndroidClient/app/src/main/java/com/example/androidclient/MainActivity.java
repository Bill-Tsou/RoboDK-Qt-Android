package com.example.androidclient;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Message;
import android.os.StrictMode;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.TextView;
import android.widget.Toast;

import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.net.UnknownHostException;
import java.nio.charset.StandardCharsets;

import javax.net.SocketFactory;

public class MainActivity extends AppCompatActivity {

    static final int MAX_READ_BYTES = 10240;

    static final int BACK_NO_MSG = 0;
    static final int BACK_UPDATE_MSG = 1001;
    //static final int BACK_IMG_MSG = 1002; // no image present in this project
    static final int BACK_BUTTON_CUBE_RESET = 1011;
    static final int BACK_BUTTON_CUBE_RAND_PLACE = 1012;
    static final int BACK_BUTTON_OP_PLACE = 1013;
    static final int BACK_BUTTON_OP_UNDO = 1014;
    static final int BACK_SEMI_MODE_AVAILABLE_BOX = 1015;

    static final String RESPOND_NO_MSG = "<NO_MSG>";
    static final int RESPOND_TIMEOUT = 1000; // in milliseconds

    private TcpWrite tcpWrite;
    private TcpRead tcpRead;
    private Thread tcpReadThread;
    private Socket socket = null;

    private Handler mForegroundHandler;
    private Handler mBackgroundHandler;

    private TextView textView_message;
    // controls of robot
    private Button btn_cube_reset, btn_cube_rand_place;
    private Button btn_op_place, btn_op_undo;
    private Button btn_pos_home, btn_pos_work;
    private Button btn_inc_tx_minus, btn_inc_tx_plus, btn_inc_ty_minus, btn_inc_ty_plus, btn_inc_tz_minus, btn_inc_tz_plus;
    private RadioButton rad_mode_auto, rad_mode_semi_auto;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);

        // TCP test controls
        Button button_connect, button_send;
        EditText editText_ip, editText_send;
        TextView textView_state;

        textView_state = findViewById(R.id.textView_State);
        textView_message = findViewById(R.id.textView_message);
        button_connect = findViewById(R.id.button_connect);
        button_send = findViewById(R.id.button_send);
        editText_ip = findViewById(R.id.editText_IP);
        editText_send = findViewById(R.id.editText_send);

        btn_cube_reset = findViewById(R.id.button_cube_reset);
        btn_cube_rand_place = findViewById(R.id.button_rand_place);
        btn_op_place = findViewById(R.id.button_op_place);
        btn_op_undo = findViewById(R.id.button_op_undo);
        btn_pos_home = findViewById(R.id.button_pos_home);
        btn_pos_work = findViewById(R.id.button_pos_work);
        btn_inc_tx_minus = findViewById(R.id.button_inc_x_minus);
        btn_inc_tx_plus = findViewById(R.id.button_inc_x_plus);
        btn_inc_ty_minus = findViewById(R.id.button_inc_y_minus);
        btn_inc_ty_plus = findViewById(R.id.button_inc_y_plus);
        btn_inc_tz_minus = findViewById(R.id.button_inc_z_minus);
        btn_inc_tz_plus = findViewById(R.id.button_inc_z_plus);
        rad_mode_auto = findViewById(R.id.rad_auto);
        rad_mode_semi_auto = findViewById(R.id.rad_semi_auto);

        // Tcp Writing Runnable
        tcpWrite = new TcpWrite();
        // Tcp Read Runnable
        tcpRead = new TcpRead();
        // Tcp Read Thread
        tcpReadThread = new Thread(tcpRead);

        // foreground and background thread initialize
        HandlerThread handlerThread = new HandlerThread("BackgroundThread");
        handlerThread.start();
        BackgroundCallback callback = new BackgroundCallback();
        mBackgroundHandler = new Handler(handlerThread.getLooper(), callback);
        mForegroundHandler = new Handler(callback);

        button_connect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(socket == null)
                {
                    try {
                        //socket = new Socket(editText_ip.getText().toString(), 1234);
                        socket = SocketFactory.getDefault().createSocket();
                        SocketAddress addr = new InetSocketAddress(editText_ip.getText().toString(), 1234);
//                        SocketAddress addr = new InetSocketAddress(editText_ip.getText().toString(), 5555);
                        // wait for 1 second to connect to server
                        socket.connect(addr, 1000);

                        button_connect.setText("Disconnect");
                        textView_state.setText("Connected");
                        SetControlEnable(true);
                    } catch (IOException e) {
                        e.printStackTrace();
                        Toast.makeText(MainActivity.this, "Cannot connect to remote!", Toast.LENGTH_SHORT).show();
                        socket = null;
                    }
                }
                else
                {
                    try {
                        socket.close();
                        socket = null;
                        button_connect.setText("Connect");
                        textView_state.setText("Disconnected");
                        SetControlEnable(false);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        button_send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String msg = editText_send.getText().toString();
                tcpWrite.sendMessage(msg, BACK_UPDATE_MSG);
            }
        });

        // listeners of control buttons
        btn_cube_reset.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tcpWrite.sendMessage("CUBE_RESET", BACK_BUTTON_CUBE_RESET);
            }
        });
        btn_cube_rand_place.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tcpWrite.sendMessage("CUBE_RAND_PLACE", BACK_BUTTON_CUBE_RAND_PLACE);
            }
        });

        rad_mode_auto.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tcpWrite.sendMessage("MODE_AUTO", BACK_NO_MSG);
                rad_mode_auto.setChecked(true);
                rad_mode_semi_auto.setChecked(false);
            }
        });
        rad_mode_semi_auto.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tcpWrite.sendMessage("MODE_SEMI_AUTO", BACK_NO_MSG);
                rad_mode_auto.setChecked(false);
                rad_mode_semi_auto.setChecked(true);
            }
        });

        btn_op_place.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tcpWrite.sendMessage("OP_PLACE", BACK_BUTTON_OP_PLACE);
            }
        });
        btn_op_undo.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tcpWrite.sendMessage("OP_UNDO", BACK_BUTTON_OP_UNDO);
            }
        });

        btn_pos_home.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tcpWrite.sendMessage("POS_HOME", BACK_NO_MSG);
            }
        });
        btn_pos_work.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tcpWrite.sendMessage("POS_WORK", BACK_NO_MSG);
            }
        });

        btn_inc_tx_minus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tcpWrite.sendMessage("INC_TX_MINUS", BACK_NO_MSG);
            }
        });
        btn_inc_tx_plus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tcpWrite.sendMessage("INC_TX_PLUS", BACK_NO_MSG);
            }
        });
        btn_inc_ty_minus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tcpWrite.sendMessage("INC_TY_MINUS", BACK_NO_MSG);
            }
        });
        btn_inc_ty_plus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tcpWrite.sendMessage("INC_TY_PLUS", BACK_NO_MSG);
            }
        });
        btn_inc_tz_minus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tcpWrite.sendMessage("INC_TZ_MINUS", BACK_NO_MSG);
            }
        });
        btn_inc_tz_plus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                tcpWrite.sendMessage("INC_TZ_PLUS", BACK_NO_MSG);
            }
        });
    }

    private void SetControlEnable(boolean enable)
    {
        btn_cube_reset.setEnabled(enable);
        btn_cube_rand_place.setEnabled(enable);
        btn_op_place.setEnabled(false); // enable after clicking rand_place
        btn_op_undo.setEnabled(false);  // enable after clicking place
        btn_pos_home.setEnabled(enable);
        btn_pos_work.setEnabled(enable);
        btn_inc_tx_minus.setEnabled(enable);
        btn_inc_tx_plus.setEnabled(enable);
        btn_inc_ty_minus.setEnabled(enable);
        btn_inc_ty_plus.setEnabled(enable);
        btn_inc_tz_minus.setEnabled(enable);
        btn_inc_tz_plus.setEnabled(enable);
        rad_mode_auto.setEnabled(enable);
        rad_mode_semi_auto.setEnabled(enable);
    }

    private class TcpWrite implements Runnable
    {
        private volatile String msg;
        private volatile int msg_num;
        DataOutputStream dos;

        @Override
        public void run() {
            try {
                dos = new DataOutputStream(socket.getOutputStream());
                //dos.writeUTF(msg);

                byte[] bytes = msg.getBytes("US-ASCII");
                dos.write(bytes);

                // can only request one message at a time
                if(msg_num != BACK_NO_MSG && !tcpReadThread.isAlive())
                    tcpRead.readMessage(msg_num);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        public void sendMessage(String msg, int msg_num)
        {
            this.msg = msg + "\r\n";
            this.msg_num = msg_num;
            new Thread(this).start();
        }
    }

    private class TcpRead implements Runnable
    {
        public volatile String msg;

        private DataInputStream dis;
        private volatile int msg_num;

        @Override
        public void run() {
            try {
                dis = new DataInputStream(socket.getInputStream());
                byte [] readBytes = new byte[MAX_READ_BYTES];

                msg = "";
                int timeout_counter = 0;
                while(timeout_counter++ < RESPOND_TIMEOUT)
                {
                    byte [] buffer = new byte[dis.available()];
                    dis.read(buffer);
                    String str = new String(buffer, StandardCharsets.US_ASCII);
                    msg += str;
                    if(msg.contains("\r\n"))
                        break;

                    Thread.sleep(1);
                }

                if(timeout_counter >= RESPOND_TIMEOUT)
                    msg = RESPOND_NO_MSG;
                else    // remove last 2 characters
                    msg = msg.substring(0, msg.length() - 2);

                Message message = new Message();
                message.what = msg_num;
                mBackgroundHandler.sendMessage(message);

            } catch (IOException | InterruptedException e) {
                e.printStackTrace();
            }
        }

        public void readMessage(int msg_num)
        {
            this.msg_num = msg_num;
            tcpReadThread = new Thread(this);
            tcpReadThread.start();
        }
    }

    private class BackgroundCallback implements Handler.Callback
    {
        @Override
        public boolean handleMessage(@NonNull Message msg) {
            switch (msg.what)
            {
                case BACK_UPDATE_MSG:
                    mForegroundHandler.post(new Runnable() {
                        @Override
                        public void run() {
                            if(!tcpRead.msg.equals(RESPOND_NO_MSG))
                                textView_message.setText(tcpRead.msg);
                            else
                                textView_message.setText("(No Message Returned)");
                        }
                    });
                    break;

                // messages of controls
                case BACK_BUTTON_CUBE_RESET:
                    if(tcpRead.msg.equals("OK"))
                    {
                        mForegroundHandler.post(new Runnable() {
                            @Override
                            public void run() {
                                btn_op_place.setEnabled(false);
                                btn_op_undo.setEnabled(false);
                            }
                        });
                    }
                    break;
                case BACK_BUTTON_CUBE_RAND_PLACE:
                case BACK_BUTTON_OP_UNDO:
                    if(tcpRead.msg.equals("OK"))
                    {
                        mForegroundHandler.post(new Runnable() {
                            @Override
                            public void run() {
                                btn_op_place.setEnabled(true);
                                btn_op_undo.setEnabled(false);
                            }
                        });
                    }
                    break;
                case BACK_BUTTON_OP_PLACE:
                    if(tcpRead.msg.equals("OK"))
                    {
                        mForegroundHandler.post(new Runnable() {
                            @Override
                            public void run() {
                                btn_op_place.setEnabled(false);
                                btn_op_undo.setEnabled(true);
                            }
                        });
                    }
                    else if(!tcpRead.msg.equals(RESPOND_NO_MSG))
                    {
                        AlertDialog.Builder builder = new AlertDialog.Builder(MainActivity.this);
                        builder.setTitle("Semi-Auto Mode Confirm");
                        builder.setMessage("Distinguished Color is " + tcpRead.msg + "\nDo you want to continue?");
                        builder.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                tcpWrite.sendMessage("SEMI_MODE_CONTINUE", BACK_BUTTON_OP_PLACE);
                            }
                        });
                        builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                tcpWrite.sendMessage("SEMI_MODE_CANCEL", BACK_NO_MSG);
                            }
                        });
                        builder.setOnCancelListener(new DialogInterface.OnCancelListener() {
                            @Override
                            public void onCancel(DialogInterface dialog) {
                                tcpWrite.sendMessage("SEMI_MODE_CANCEL", BACK_NO_MSG);
                            }
                        });
                        builder.setNeutralButton("Other Options...", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                tcpWrite.sendMessage("SEMI_MODE_AVAILABLE_BOX", BACK_SEMI_MODE_AVAILABLE_BOX);
                            }
                        });
                        builder.show();
                    }
                    break;

                case BACK_SEMI_MODE_AVAILABLE_BOX:
                {
                    AlertDialog.Builder manualDialog = new AlertDialog.Builder(MainActivity.this);
                    manualDialog.setTitle("Semi-Auto Mode Confirm");
                    manualDialog.setMessage("Which box would you like to put?");
                    if(tcpRead.msg.contains("RED"))
                        manualDialog.setNeutralButton("Red", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                tcpWrite.sendMessage("SEMI_MODE_RED_BOX", BACK_BUTTON_OP_PLACE);
                            }
                        });
                    if(tcpRead.msg.contains("GREEN"))
                        manualDialog.setNegativeButton("Green", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                tcpWrite.sendMessage("SEMI_MODE_GREEN_BOX", BACK_BUTTON_OP_PLACE);
                            }
                        });
                    if(tcpRead.msg.contains("BLUE"))
                        manualDialog.setPositiveButton("Blue", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                tcpWrite.sendMessage("SEMI_MODE_BLUE_BOX", BACK_BUTTON_OP_PLACE);
                            }
                        });
                    manualDialog.setOnCancelListener(new DialogInterface.OnCancelListener() {
                        @Override
                        public void onCancel(DialogInterface dialog) {
                            tcpWrite.sendMessage("SEMI_MODE_CANCEL", BACK_NO_MSG);
                        }
                    });
                    manualDialog.show();
                }
                    break;
            }
            return true;
        }
    }

}