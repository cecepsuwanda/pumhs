<?php
if(isset($_SESSION["usr"])){
$server = $_SERVER['DOCUMENT_ROOT'];
$usr = $_SESSION["usr"];

if ($usr == "root" ){
$host="localhost"; 

    if($server=="/home/uni10000/public_html/pumhs") {
       $username_sys="uni10000_admin"; 
       $password_sys="bismillah2013";      		
	} 
    else{
	   $username_sys="root"; 
       $password_sys="";    
	}
  
  
}

if ($usr == "admin") {
$host="localhost"; 
$username_sys="admin"; 
$password_sys=""; 
}

if ($usr == "user") {
$host="localhost"; 
$username_sys="user"; 
$password_sys=""; 
}

if ($usr == "guest") {
$host="localhost"; 
$username_sys="guest"; 
$password_sys=""; 
}

if($server=="/home/uni10000/public_html/pumhs") {
     $database="uni10000_pumhs";            		
	} 
    else{
	 $database="pumhs";     
	}

 

mysql_connect("$host", "$username_sys", "$password_sys")or die("gagal melakukan koneksi!!!");
mysql_select_db("$database")or die("Database tidak ditemukan di server");
}
else echo "tidak boleh koneksi langsung";
?>