<?php

?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
	<head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <meta name="language" content="en">

        <!-- blueprint CSS framework -->
        <link rel="stylesheet" type="text/css" href="../css/screen.css" media="screen, projection">
        <link rel="stylesheet" type="text/css" href="../css/print.css" media="print">
        <!--[if lt IE 8]>
        <link rel="stylesheet" type="text/css" href="/css/ie.css" media="screen, projection" />
        <![endif]-->
        <link rel="stylesheet" href="../css/css.css">
        <link rel="stylesheet" type="text/css" href="../css/main.css">
        <link rel="stylesheet" type="text/css" href="../css/form.css">
        <link rel="stylesheet" href="../css/select2.css">
        <link rel="icon" type="image/png" href="../image/unibbaicon.png">
        <link rel="stylesheet" type="text/css" href="../css/jquery-ui.css">

		<script type="text/javascript" src="../js/jquery_002.js"></script>
		<script type="text/javascript" src="../js/jquery_login.js"></script>
		<script type="text/javascript" src="../js/jquery-ui.js"></script>
		<title>PUMHS - Reset Password</title>
		
		<style type="text/css">
	      @import "../datatables/media/css/demo_page.css";
	      @import "../datatables/media/css/demo_table.css";
          .ui-widget { font-family: Trebuchet MS, Tahoma, Verdana, Arial, sans-serif; font-size: 12px; }		  
        </style>
		
		<script type="text/javascript" src="../datatables/media/js/jquery.dataTables.js"></script>
		
		
    </head>
<body>
<script type="text/javascript">
    var oTable1,oTable2,oTable3,oTable4;
	$(document).ready(function () {
	   $("#data").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   
	   $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
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
	    $("#data"+(idx)).html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
		
	  //if(oTable4 != null)oTable4.fnDestroy();
	  //if(oTable1 != null)oTable1.fnDestroy();
	  //if(oTable2 != null)oTable2.fnDestroy();
	  //if(oTable3 != null)oTable3.fnDestroy();
	     
	  $.ajax({
                                     type : "POST",
				                     url : "chg_conten.php",
				                     cache: false,
				                     data :"idx="+(idx+1),
									 success : function(data){												
												$("#data"+(idx)).html(data);
												if(idx==5){
												  oTable1=$("#tb_login").dataTable({"aaSorting": []});
				                                  oTable2=$("#tb_create").dataTable({"aaSorting": []});
				                                  oTable3=$("#tb_update").dataTable({"aaSorting": []});
												 }else{
												 
												 oTable4=$("#lst_mhs"+idx).dataTable({"aaSorting": []});
												 }
												  
				                               }
                                  }); 
	   
	   
   }
</script>


<div class="container" id="page">
<div id="header">
    <a href="http://www.unibba.ac.id/">
        <img src="../image/header3.png" height="110" width="1000">
    </a>
</div><!-- header -->
<div id="content">

<div id="loginContainer">

<br>
<h1>Reset Password</h1>
	<div class="form">
	<form id="login-form" action="rst_pass.php" method="post">
		<label>Nomor KTP</label><input name="nomorKTP" id="nomorKTP" type="text" value="">		
		<div class="errorMessage" id="nomorKTP_em_" style="display:none"></div>	
		<label>Password Baru</label><input name="password" id="password" type="password">		
		<div class="errorMessage" id="password_em_" style="display:none"></div><br>	
		 
		<input name="btnSubmit" value="Reset" type="submit"><br>
		
	</form>
	</div><!-- form -->
</div>
<br>
<div  id='data'> </div>
</div><!-- content -->
<div class="clear"></div>

<div id="footer">
<p>
Jalan RAA. Wiranatakusuman No. 7 Bale Endah Bandung <br>
Telepon (022) 594 0443, 594 0262, 594 7087 <br>
Fax (022) 594 0443 <br>
Situs <a href="http://www.unibba.ac.id/">www.unibba.ac.id</a> <br><br>

© PUMHS Pendataan Ulang Mahasiswa 2013 <br>
<!--Copyright &copy; 2013 by FTI Unibba<br/>
All Rights Reserved.<br/>
-->
</p>
</div><!-- footer -->
</div><!-- page -->
<script type="text/javascript">
jQuery(function($) 
{
	jQuery('#login-form').yiiactiveform(
		{'validateOnSubmit':true,
			'attributes':
			[
				{
					'id':'nomorKTP',
					'inputID':'nomorKTP',
					'errorID':'nomorKTP_em_',
					'model':'LoginForm',
					'name':'nomorKTP',
					'enableAjaxValidation':false,
					'clientValidation':
						function(value, messages, attribute) 
						{
							if(jQuery.trim(value)=='') {messages.push("Nomor KTP tidak boleh kosong.");}
						}
				},
				{
					'id':'password',
					'inputID':'password',
					'errorID':'password_em_',
					'model':'LoginForm',
					'name':'password',
					'enableAjaxValidation':false,
					'clientValidation':
						function(value, messages, attribute) 
						{
							if(jQuery.trim(value)=='') {messages.push("Password tidak boleh kosong.");}
						}
				}
			]
		});
});
/*]]>*/
</script>
</body>
</html>