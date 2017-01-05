<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<%@ page import="java.io.*, java.net.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Insert title here</title>
</head>
<body>
        <H1>DOS IOT Web Application</H1>
        <button id= "ShowSensors" type="button" >ShowSensors</button>
        <button id= "LEDSensor" type="button" hidden="true" >LED!</button>
        <button id= "SegmentSensor" type="button" hidden="true" >7 segment</button>
        <button id= "TemperatureSensor" type="button" hidden="true" >Temperature sensor</button>
        <button id= "ONLED" type="button" hidden="true">On </button>
        <button id= "OFFLED" type="button" hidden="true">OFF </button>
        <button id= "ReadLED" type="button" hidden="true"> Read </button>
         <label id= "LEDLabel" hidden= "true"> Give Input Value:</label> <input id="LEDInput" type="text" hidden="true">
         <button id= "Submit" type="button" hidden="true"> Submit </button>
         <br>
         <label id= "LEDStatus" hidden= "true"> </label>
        <label id= "TemperatureLabelInt" hidden= "true"></label>
        <label id= "TemperatureLabelDec" hidden= "true"> </label>
        <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
        <script>
        
        	$(function() {
				
        		//ajaxCall("Ready");
        		//var d= receiveData();
        		
        	});
        	
        	$( "#ShowSensors" ).click(function(){
        			
        		var name = "sensors";
                ajaxCall(name);
        		$("#LEDSensor").show();
        		$("#SegmentSensor").show();
        		$("#TemperatureSensor").show();
        	});
        	
        	$( "#LEDSensor" ).click(function() {
        		
        		$("#ONLED").show();
        		$("#OFFLED").show();
        		$("#ReadLED").show();
        	});
        	
			$( "#ONLED" ).click(function() {
        		
				ajaxCall("ONLED");
        		
        	});
        	
			$( "#OFFLED" ).click(function() {
				ajaxCall("OFFLED");
        		
        	});
			
			$( "#ReadLED" ).click(function() {
				ajaxCall("ReadLED");
				var d= receiveData();
        		$("#LEDStatus").show();
        		$("#LEDStatus").val("LES status is "+d);
        		 document.getElementById("LEDStatus").value = "LES status is "+d;
        	});
			
        	$( "#SegmentSensor" ).click(function() {
        		
        		$("#LEDLabel").show();
        		$("#LEDInput").show();
        		$("#Submit").show();
        	});
        	
			$( "#Submit" ).click(function() {
        		
				var input = $("#LEDInput").val();
				var s = "SSD"+ input;
			
        		ajaxCall(s);
        		$("#LEDLabel").hide();
        		$("#LEDInput").hide();
        		$("#Submit").hide();
        	});	
			
        	$( "#TemperatureSensor" ).click(function() {
        		
        		ajaxCall("temp");
        		var status = receiveData();
        		
        		//var integ = receiveData();
        	
        		$("#TemperatureLabelInt").show();
        		$("#TemperatureLabelInt").val(status);
        		
        		//$("#TemperatureLabelDec").show();
        		document.getElementById("TemperatureLabelInt").value =status;
        		//var dec = receiveData();
        		
				
				//$("#TemperatureLabelDec").val(dec);
				
			});
        	
        	function ajaxCall(d){
       		 $.ajax({
       	            url:'ConnectToServer',
       	            data:{name:d},
       	            type:'get',
       	            cache:false,
       	            success:function(data){
       
       	                },
       	            error:function(){
       	              
       	            }
       	         });
       		 
       		};
       		
       		function receiveData(){
        		var d;
          		 $.ajax({
          	            url:'ReceiveDataFromServer',
          	            data:{name:""},
          	            type:'get',
          	            cache:false,
          	            success:function(data){
          	            	d = data;
          	                },
          	            error:function(){
          	            
          	            }
          	         });
          			return d;
       			};
        	
        </script>
	
</body>
</html>