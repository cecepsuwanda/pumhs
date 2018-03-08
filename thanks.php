<?php
//session_start();
if(isset($_SESSION['username']))
   unset($_SESSION['username']);
if(isset($_SESSION['NO_KTP']))
   unset($_SESSION['NO_KTP']);   
?> 
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
    <head>
        <link rel="stylesheet" type="text/css" href="css/screen.css" media="screen, projection" />
        <link rel="stylesheet" type="text/css" href="css/print.css" media="print" />
        <!--[if lt IE 8]>
        <link rel="stylesheet" type="text/css" href="/beasiswa/css/ie.css" media="screen, projection" />
        <![endif]-->
        <link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Oxygen:400,300,700" />
        <link rel="stylesheet" type="text/css" href="css/main.css" />
        <link rel="stylesheet" type="text/css" href="css/form.css" />
        <link rel="stylesheet" href="css/select2.css" />
		<link rel="icon" type="image/png" href="image/iconunibba.png">
		
		<link rel="stylesheet" type="text/css" href="css/jquery-ui.css">

		<script type="text/javascript" src="js/jquery_002.js"></script>
		<script type="text/javascript" src="js/jquery_login.js"></script>
		<script type="text/javascript" src="js/jquery-ui.js"></script>
		
		<style type="text/css">
	      @import "datatables/media/css/demo_page.css";
	      @import "datatables/media/css/demo_table.css";
          .ui-widget { font-family: Trebuchet MS, Tahoma, Verdana, Arial, sans-serif; font-size: 12px; }		  
        </style>
		
		<script type="text/javascript" src="datatables/media/js/jquery.dataTables.js"></script>

    </head>
<body>
<script type="text/javascript">
    var oTable1,oTable2,oTable3,oTable4;
	$(document).ready(function () {
	   $("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='image/ajax-loader.gif' /></div>");
	   
	   $.ajax({
                                     type : "POST",
				                     url : "pumhs/chg_conten.php",
				                     cache: false,
				                     data :"idx=1",
									 success : function(data){
					                            $("#data").html(data);	
												$( "#tabs" ).tabs();
												$( "#tabs1" ).tabs();																								
												$( "#tabs2" ).tabs();
												
												oTable1=$("#tb_login").dataTable({"aaSorting": []});
				                                oTable2=$("#tb_create").dataTable({"aaSorting": []});
				                                oTable3=$("#tb_update").dataTable({"aaSorting": []});
												oTable4=$("#lst_mhs7").dataTable({"aaSorting": []});
				                               }
                                  });
	   
	   
	   
	  

   });
   
   function ch_cont_tab(idx){
	    $("#data"+(idx)).html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='image/ajax-loader.gif' /></div>");
		
	  //if(oTable4 != null)oTable4.fnDestroy();
	  //if(oTable1 != null)oTable1.fnDestroy();
	  //if(oTable2 != null)oTable2.fnDestroy();
	  //if(oTable3 != null)oTable3.fnDestroy();
	     
	  $.ajax({
                                     type : "POST",
				                     url : "pumhs/chg_conten.php",
				                     cache: false,
				                     data :"idx="+(idx+1),
									 success : function(data){												
												$("#data"+(idx)).html(data);
												if(idx==1){
												  oTable1=$("#tb_login").dataTable({"aaSorting": []});
				                                  oTable2=$("#tb_create").dataTable({"aaSorting": []});
				                                  oTable3=$("#tb_update").dataTable({"aaSorting": []});
												 }else{
												 
												 oTable4=$("#lst_mhs"+idx).dataTable({"aaSorting": []});
												 }
												  
				                               }
                                  }); 
	   
   function filter_mhs()
   {
      $("#data_mhs").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   var prodi = $("#Prodi_krsmhs").val();	
       	
       
	  $.ajax({
                                     type : "POST",
				                     url : "pumhs/chg_conten.php",
				                     cache: false,
				                     data :"idx=10&prodi="+prodi,
									 success : function(data){
					                            $("#data_mhs").html(data);												
										        oTable1=$("#lst_mhs7").dataTable({"aaSorting": []});
				                               }
                                  });
   
   }  
   
   
   }
</script>
<div id="content"> 
<div id="header">
<a href="http://www.unibba.ac.id"><img src="image/header3.png" height="110" width="1000"></a>
</div><!-- header -->
<div id="reg">
<h2>*** TERIMA KASIH ***</h2>
Terimakasih anda sudah membantu kami mengisi PUMHS<br>
anda sudah mendukung langkah menuju UNIBBA berbasis IT<br>
<a href="index.php">untuk melengkapi data silahkan login (klik disini)</a>
</div>
<div  id='data'> </div>
</div>
</body>
</html>