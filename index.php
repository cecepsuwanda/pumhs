<?php 

   require_once 'shared.php'; 

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
	   
	   
   }
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
   
   function filter_mtk()
   {
      $("#data_mtk").html("<div id='pgload'><font size='1' color='red'>Mengontak Server ....</font> <img src='../image/ajax-loader.gif' /></div>");
	   var prodi = $("#Prodi_krsmtk").val();	
       	
       
	  $.ajax({
                                     type : "POST",
				                     url : "pumhs/chg_conten.php",
				                     cache: false,
				                     data :"idx=11&prodi="+prodi,
									 success : function(data){
					                            $("#data_mtk").html(data);												
										        oTable1=$("#lst_mhs8").dataTable({"aaSorting": []});
				                               }
                                  });
   
   }
</script>


<div class="container" id="page">
<div id="header">
    <a href="http://www.unibba.ac.id/">
        <img src="image/header3.png" height="110" width="1000">
    </a>
</div><!-- header -->
<div id="content">
<?php

if(!isset($_SESSION['_message'])){
?>
<div id="reg">
Pendataan Ulang Mahasiswa (PUMHS) merupakan langkah awal Universitas Bale Bandung menjadi Universitas berbasis IT,
<br>kepada mahasiswa baru  lama diharapkan  mendukung langkah ini dengan membantu mengisi data identitasnya.
<br>
<br>Kami Tim Pengembang Sistem Informasi Universitas Bale Bandung sangat berterimakasih kepada mahasiswa yang bersedia
untuk memberikan kontribusinya dengan melakukan <a href="form_add_pumhs_acc.php">Registrasi/ Pendaftaran disini (silahkan klik)</a></br>
<br>Jika anda mengalami kesulitan, silakan hubungi kami di <a href="http://www.facebook.com/psi.unibba">http://www.facebook.com/psi.unibba</a></br>
</div>
<br>
<?php
}
?>
<div id="loginContainer">
<?php
$ktp="";
if(isset($_SESSION['_message'])){ 
	if ($_SESSION['_message'] == "sudah ada") {
		echo "Nomor KTP yang anda masukan sudah terdaftar, silahkan login bila anda akan melengkapi data identitasnya <br>";
		$ktp=$_SESSION['ktp'];
		}
	elseif ($_SESSION['_message'] == "password_salah") {
		echo " password yang anda masukkan salah, ulangi login <br>";
		echo " jika anda lupa password, silahkan gunakan fasilitas reset password, anda cukup menginput nomor KTP dan Password Baru! <br>";
		$ktp=$_SESSION['ktp'];
		}
	elseif ($_SESSION['_message'] == "lengkapi_data"){
		echo " untuk melengkapi data<br>, silahkan login terlebih dahulu <br> terimakasih <br>";
		$ktp=$_SESSION['ktp'];
		}
	}
else {
	echo "Bagi yang sudah terdaftar dan akan melengkapi identitasnya atau mengupdatenya silahkan login disini:<br>";
	}
session_destroy();
?>
<br>
<h1>Login</h1>
	<div class="form">
	<form id="login-form" action="login.php" method="post">
		<label>Nomor KTP</label><input name="nomorKTP" id="nomorKTP" type="text" value="<?php echo $ktp ?>">		
		<div class="errorMessage" id="nomorKTP_em_" style="display:none"></div>	
		<label>Password</label><input name="password" id="password" type="password">		
		<div class="errorMessage" id="password_em_" style="display:none"></div><br>	
		Bagi yang sudah terdaftar <br> 
		<input name="btnSubmit" value="Login" type="submit"><br>
		Bagi yang belum terdaftar <br> 
		<a href="form_add_pumhs_acc.php">Registrasi/ Pendaftaran disini (silahkan klik)</a><br>
		Bagi yang lupa password <br> 
		<a href="pumhs/frm_rst_pass.php">Reset Password</a><br>
		Bantuan atau Masukan <br> 
		<a href="pumhs/viewguestbook.php">Bantuan</a><br>
	</form>
	</div><!-- form -->
</div>
<br>
  <div  id='data'></div>
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