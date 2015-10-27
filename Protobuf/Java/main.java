package main;

import java.io.InputStream;
import java.net.Socket;
import java.net.UnknownHostException;

import com.protobuf.msg.*;
import com.protobuf.msg.Messages.Message;
import com.protobuf.msg.ResponseOuterClass.Response;
import com.protobuf.msg.User.Info;
public class main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String host = "127.0.0.1";
        int port = 3000;
        Info info = User.Info.newBuilder().setId(1).setName("test,im JAVA!"+Math.random()).build();
        Message sendMsg = Messages.Message.newBuilder()
        								.setTypeValue(Status.msgType.WORK_VALUE)
        								.setMsgBodyBytes(info.toByteString())
        								.build();

        try {
            Socket client = new Socket(host, port);


            // Send message to Server
            byte[] result = sendMsg.toByteArray() ;
            client.getOutputStream().write(result); 

            // Receive message from Server
            InputStream input = client.getInputStream();

            byte[] msg = recvMsg(input);
            Response r = Response.parseFrom(msg);

            System.out.println("Type value:\t\t"+r.getTypeValue());
            System.out.println("Type:\t\t"+r.getType());
            System.out.println("Status:\t\t"+r.getStatus());
            System.out.println("Data:\t\t"+r.getData());

            input.close();
            client.close();
        } catch (UnknownHostException e){
            System.out.println("UnknownHostException:" + e.toString());
        } catch (java.io.IOException e) {
            System.out.println("IOException :" + e.toString());
            e.printStackTrace();
        }
	}
	
	/**
     * Receive mssage from Server
     * 
     * @return
     */
    public static byte[] recvMsg(InputStream inpustream) {
        try {

            byte len[] = new byte[1024];
            int count = inpustream.read(len); 

            byte[] temp = new byte[count];
            for (int i = 0; i < count; i++) { 
                temp[i] = len[i]; 
            } 
            return temp;
        } catch (Exception e) {
            System.out.println("recvMsg() occur exception!" + e.toString());
        }
        return null;
    }
}
