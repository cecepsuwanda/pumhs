<?php
 session_start(); 
 $server = $_SERVER['DOCUMENT_ROOT'];
 $base_path = $server . '/pumhs/cecep/';
 if(!is_dir($base_path)){
   if($server=="/home/uni10000/public_html/pumhs") {
        $base_path = $server . '/cecep/';		
	} 
    else{
	  $base_path = $server . '/pumhs/cecep/';	 
	}  
 }
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
        <link rel="stylesheet" type="text/css" href="../css/ie.css" media="screen, projection" />
        <![endif]-->
        <link rel="stylesheet" href="css/css.css">
        <link rel="stylesheet" type="text/css" href="../css/main.css">
        <link rel="stylesheet" type="text/css" href="../css/form.css">
        <link rel="stylesheet" href="../css/select2.css">
        <link rel="icon" type="image/png" href="../image/iconunibba.png">
        <link rel="stylesheet" type="text/css" href="../css/jquery-ui.css">

		<script type="text/javascript" src="../js/jquery_002.js"></script>
		<script type="text/javascript" src="../js/jquery_login.js"></script>
		<script type="text/javascript" src="../js/jquery-ui.js"></script>
		<title>PUMHS - Login</title>		
		
    </head>
<body>



<div class="container" id="page">
<div id="header">
    <a href="http://www.unibba.ac.id/">
        <img src="../image/header3.png" height="110" width="1000">
    </a>
</div><!-- header -->
<div id="content">

<div id="loginContainer">
<?php
$userName="";
if(isset($_SESSION['_message'])){ 
	if ($_SESSION['_message'] == "password_salah") {
		echo " password yang anda masukkan salah, ulangi login <br>";
		//echo " jika anda lupa password, silahkan hubungi admin, <br> sms ke 02292444140, <br> ketikan nomor KTP anda dan Nama anda! <br>";
		$userName=$_SESSION['userName'];
		}
	if ($_SESSION['_message'] == "user_tidak_terdaftar") {
		echo "Anda belum terdaftar sebagai user<br>";
		
		$userName=$_SESSION['userName'];
		}
	}
session_destroy();
?>
<br>
<h1>Login</h1>
	<div class="form">
	<form id="login-form" action="admin_login.php" method="post">
		<label>User Name</label><input name="userName" id="userName" type="text" value=<?php echo $userName; ?>>		
		<div class="errorMessage" id="userName_em_" style="display:none"></div>	
		<label>Password</label><input name="password" id="password" type="password">		
		<div class="errorMessage" id="password_em_" style="display:none"></div><br>
        <input name="btnSubmit" value="Login" type="submit"><br>		
	</form>
	</div><!-- form -->
</div>
<br>

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
					'id':'userName',
					'inputID':'userName',
					'errorID':'userName_em_',
					'model':'LoginForm',
					'name':'userName',
					'enableAjaxValidation':false,
					'clientValidation':
						function(value, messages, attribute) 
						{
							if(jQuery.trim(value)=='') {messages.push("User Name tidak boleh kosong.");}
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