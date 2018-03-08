<?php
 
include_once "shared.php"; 
$vw_mhs = new vw_mhs;
$idx = $_GET['idx'];

?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
	<head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <meta name="language" content="en">

        <!-- blueprint CSS framework -->
        <link rel="stylesheet" type="text/css" href="css/screen.css" media="screen, projection">
        <link rel="stylesheet" type="text/css" href="css/print.css" media="print">
        <!--[if lt IE 8]>
        <link rel="stylesheet" type="text/css" href="/css/ie.css" media="screen, projection" />
        <![endif]-->
        <link rel="stylesheet" href="css/css.css">
        <link rel="stylesheet" type="text/css" href="css/main.css">
        <link rel="stylesheet" type="text/css" href="css/form.css">
        <link rel="stylesheet" href="css/select2.css">
        <link rel="icon" type="image/png" href="image/iconunibba.png">
        <link rel="stylesheet" type="text/css" href="css/jquery-ui.css">

		<script type="text/javascript" src="js/jquery_002.js"></script>
		<script type="text/javascript" src="js/jquery_login.js"></script>
		<script type="text/javascript" src="js/jquery-ui.js"></script>
		<title>PUMHS - Login</title>
		
		<style type="text/css">
	      @import "datatables/media/css/demo_page.css";
	      @import "datatables/media/css/demo_table.css";
          .ui-widget { font-family: Trebuchet MS, Tahoma, Verdana, Arial, sans-serif; font-size: 12px; }		  
        </style>
		
		<script type="text/javascript" src="datatables/media/js/jquery.dataTables.js"></script>
		
		
    </head>
<body>
<script type="text/javascript">
    $(document).ready(function () {
	   //$("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='image/ajax-loader.gif' /></div>");
	  oTable1=$("#lst_mhs").dataTable({"aaSorting": []});
   });
   
   function ch_cont_tab(idx){
   
   
   
   
   
   }
   
</script>
  <?php 
   switch($idx){
   case 1 :  echo $vw_mhs->lst_entry_data(0,"lst_mhs",1); break; 
   case 2 :  echo $vw_mhs->lst_entry_data(0,"lst_mhs",2); break;
   case 3 :	 echo $vw_mhs->lst_entry_data(1,"lst_mhs");break;
   case 4 :	 echo $vw_mhs->lst_entry_data(2,"lst_mhs");break;
  
  }
  ?>
</body>
</html>