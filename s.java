import java.io.*;
import java.net.*;

public class s
{    
    public static void main(String[] args ) throws IOException {
    ServerSocket serverSocket = null;
    Socket insocket;
    ServerSocket socket = new ServerSocket(8765);
	
    	//receiveFromXinu();
    	//sendDataToXinu("5");
    	//sendDataToJSP("FROM SERVER");
    	int i=0;
    	//String[] inn={"ready","sensors","ONLED","OFFLED","ReadLED","SSD","temp"};
    	while(true){
    	//while(i<7){
    		try{
    		
    		insocket = socket.accept( );
    		BufferedReader in = new BufferedReader (new 
	            InputStreamReader(insocket.getInputStream()));
	        PrintWriter out = new PrintWriter (insocket.getOutputStream(), 
	            true);
		
	        String instring = in.readLine();
	        //String statusLED,statusSSD,temp;
	        //statusLED="dummy";
	        //statusSSD="dummy1";
	        //temp="dummy2";
	      //  sendDataToXinu(instring);
	        //String instring = inn[i++];
	        System.out.println("The server got this: " + instring);
	        if(instring.equals("ready")){
	        	System.out.println("INCOMING");
	        	//sendDataToJSP("HELLO FROM SERVER");
	        }
	        else if(instring.equals("sensors")){
	        	sendDataToXinu("0");
	        	String statusLED = receiveFromXinu();
	        	//sendDataToJSP(statusLED);
	        	sendDataToXinu("1");
	        	String statusSSD= receiveFromXinu();
	        	//sendDataToJSP(statusSSD);
	        	sendDataToXinu("2");
	        	String temp=receiveFromXinu();
	        	//sendDataToJSP(temp);
	        }
	        else if(instring.equals("ONLED")){
	        	sendDataToXinu("4");
	        	String statusLED = receiveFromXinu();
	        	//sendDataToJSP(statusLED);
	        	
	        }
	        else if(instring.equals("OFFLED")){
	        	sendDataToXinu("5");
	        	String statusLED = receiveFromXinu();
	        	//sendDataToJSP(statusLED);
	        	
	        }
			else if(instring.equals("ReadLED")){
				sendDataToXinu("3");
	        	String statusLED = receiveFromXinu();
	        	int tmp=(statusLED.charAt(0)-48);
	        	statusLED=""+tmp;
	        	sendDataToJSP(statusLED);
			}
			else if(instring.substring(0,3).equals("SSD")){
				sendDataToXinu("6");
	        	String statusLED = receiveFromXinu();
	        	//sendDataToJSP(statusLED);
	        	//instring="5";
	        	//instring = in.readLine();
	        	instring=""+instring.charAt(3);
	        	sendDataToXinu(instring);
	        	statusLED = receiveFromXinu();
	        	//sendDataToJSP(statusLED);
			}
			else if(instring.equals("temp")){
				sendDataToXinu("7");
	        	String status = receiveFromXinu();
	        	//String status = "56Deg";
	        	//sendDataToJSP(status);
	        	
	        	String integer = receiveFromXinu();
	        	int tmp=(integer.charAt(0)-48)*100 ;
	        	integer = receiveFromXinu();
	        	tmp+=(integer.charAt(0)-48)*10 ;
	        	integer = receiveFromXinu();
	        	tmp+=(integer.charAt(0)-48);
	        	//integer+='\0';
	        	//String decimal = receiveFromXinu();
	        	//int tmp=(integer.charAt(0)-48)*100 + (integer.charAt(1)-48)*10 + (integer.charAt(2)-48);
	        	System.out.println("Temperature Value "+tmp);
	        	tmp=(tmp-500)/10;
	        	integer=""+tmp;
	        	sendDataToJSP(integer);
	        	//sendDataToJSP(decimal);
			}
	        
	        
	        //out.println("The server got this: " + instring);
    		}
    		finally{}
    	}
    	
    } 
    	
    public static void sendDataToXinu(String data) throws IOException{
    	
    	
    	  DatagramSocket clientSocket = new DatagramSocket(8080);
          InetAddress IPAddress = InetAddress.getByName("0xC0A80068");
          byte[] sendData = new byte[1024];
          //String sentence = inFromUser.readLine();
          //String sentence = "Hey Protocol";
          sendData = data.getBytes();
          
         
          DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, 8080);
          clientSocket.send(sendPacket);
          System.out.println("SENT TO XINU (IP->"+IPAddress+"): Message->"+data);
          clientSocket.close();
         
    }
    
    public static String receiveFromXinu() throws IOException{
    	
    
	    	DatagramSocket serverSocket = new DatagramSocket(8080);
	        byte[] receiveData = new byte[1024];
        
	      DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
	      serverSocket.receive(receivePacket);
	      String sentence = new String( receivePacket.getData());
	      //System.out.println("RECEIVED: " + sentence);
	      InetAddress IPAddress = receivePacket.getAddress();
	      int port = receivePacket.getPort();
	      System.out.println("RECEIVED FROM XINU (IP->" + IPAddress +"): Message->"+sentence);
	      serverSocket.close();
	      return sentence;
    }
 
    public static void sendDataToJSP(String data) throws UnknownHostException, IOException{
    	
    	 System.out.println("SENDING DATA "+data);
         Socket clientSocket = new Socket("192.168.0.102", 7777);
         DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
         //BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

         outToServer.writeBytes(data);
         clientSocket.close();
         
    }
}