

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Servlet implementation class ConnectToServer
 */
@WebServlet("/ConnectToServer")
public class ConnectToServer extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public ConnectToServer() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		 doPost(request, response);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		   String text = "Update successfull"; //message you will recieve 
		    String name = request.getParameter("name");
		    sendDataToServer(name);
		    System.out.println(name + " " + text);
	}

	public void sendDataToServer(String data) throws UnknownHostException, IOException{
		
		    String sentence;
	        
	        Socket clientSocket = new Socket("192.168.0.103", 8765);
	        DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
	      
	        sentence =data;
	        outToServer.writeBytes(sentence + '\n');
	        clientSocket.close();
		
	}
}
