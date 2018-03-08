<?php
		require_once 'shared.php';
?>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <meta name="language" content="en" />

        <!-- blueprint CSS framework -->
        <link rel="stylesheet" type="text/css" href="css/screen.css" media="screen, projection" />
        <link rel="stylesheet" type="text/css" href="css/print.css" media="print" />
        <!--[if lt IE 8]>
        <link rel="stylesheet" type="text/css" href="css/ie.css" media="screen, projection" />
        <![endif]-->
        <link rel="stylesheet" href="http://fonts.googleapis.com/css?family=Oxygen:400,300,700" />
        <link rel="stylesheet" type="text/css" href="css/main.css" />
        <link rel="stylesheet" type="text/css" href="css/form.css" />
        <link rel="stylesheet" href="css/select2.css" />

        <link rel="icon" type="image/png" href="image/iconunibba.png">
        <link rel="stylesheet" type="text/css" href="css/jquery-ui.css" />
		<link rel="stylesheet" type="text/css" href="css/jqueryslidemenu.css" />
		<script type="text/javascript" src="js/jquery.js"></script>
		<script type="text/javascript" src="js/jquery-ui.min.js"></script>
		<!--<script type="text/javascript" src="js/jqueryslidemenu.js"></script>-->
		<title>Pendataan Ulang Mahasiswa UNIBBA</title>
    </head>
<body>
<script>
    $(function() {
        $( "#tanggalLahir" ).datepicker({            
            dateFormat: 'yy-mm-dd',
            changeMonth: true,
            changeYear: true,
            maxDate: "-17Y",
            minDate: "-60Y",
            yearRange: "-60:-17"
        });  
              
    });
    
    function checkPassword(){
        var password1 = $("#password").val();
        var password2 = $("#konfirmasiPassword").val();
        
        if(password1 != password2) {
            $("#konfirmasiPassword").val('');
            alert("Konfirmasi Password Tidak Cocok"); 
        }
    };

    function checkKTP(){
        var ktp = $("#ktp").val();
        var t = $("#tanggalLahir").val();
		var sTgl = t.substr(9,1)+t.substr(5,2)+t.substr(2,2); 
		err = 1;
		if (ktp.search(sTgl)==7) err = 0;
		if (ktp == "") err = 0;
		if (sTgl == "") err = 0;
		if (err == 1)
		{
			alert("tgl lahir dan nomor ktp-nya tidak cocok !");
			$("#ktp").val("");
		}
     };
	 
	 function cekform(){	  
       var t1 = $("#tanggalLahir").val();	
       var nm = $("#namaMahasiswa").val();
	   
	   if($("#ktp").val()=="")
	   {
	     alert("NO KTP tidak boleh kosong !!!");
	     return false;
	   }else if (nm.trim()==""){
	     alert("Nama tidak boleh kosong, dan terdiri dari lebih satu huruf !!!");
	     return false;
	   }else if ($("#jenisKelamin").val()==""){
	     alert("Jenis Kelamin tidak boleh kosong !!!");
	     return false;
	   }else if (t1==""){
	     alert("Tanggal Lahir tidak boleh kosong !!!");
	     return false;
	   }else if ($("#password").val()==""){
	     alert("Password tidak boleh kosong !!!");
	     return false;
	   }else if ($("#konfirmasiPassword").val()==""){
	     alert("Konfirmasi Password tidak boleh kosong !!!");
	     return false;
	  } else if ($("#konfirmasiPassword").val()==""){
	     alert("Konfirmasi Password tidak boleh kosong !!!");
	     return false;
	  } else if ($("#prodi").val()==""){
	     alert("Fakultas dan Prodi tidak boleh kosong !!!");
	     return false;
	  } else if ($("#tahunMasuk").val()==""){
	     alert("Tahun Masuk tidak boleh kosong !!!");
	     return false;
	  } else {
	            $("#user-form").submit();
	        }
	   
	   
	 };
	 
	 function isNumberKey(evt)
      {
         var charCode = (evt.which) ? evt.which : event.keyCode
         if (charCode > 31 && (charCode < 48 || charCode > 57))
            return false;

         return true;
      };

</script>

<div class="container" id="page">
<div class="clear"></div>

<div id="header">
<a href="index.php"><img src="image/header3.png" height="110" width="1000"></a>
</div><!-- header -->

<div id="wrapper" style="margin-top: -20px;">
    <!-- breadcrumbs -->
<div id="content">
	
<h1>Data Account Mahasiswa</h1>

<div class="form">

    <form enctype="multipart/form-data" id="user-form" action="add_pumhs_acc.php" method="post">    
	<?php
		//session_start();
		$ktp="";
		
		if (isset($_SESSION['_message'])){
			if ($_SESSION['_message'] == "identitas_salah") {
				$ktp = $_SESSION['ktp'];
				echo "<p class='note'><a href='index.php'> Nomor identitas salah silahkan mengulagi login dengan klik disini</a></p>";
				echo "<p class='note'>atau Identitas anda belum terdaftar,silahkan lengkapi data berikut ini</p>";
			}
		}			
	?>
    <p class="note">Catatan : semua isian bertanda * perlu diisi.</p>
	<h3>Account</h3>
	
    <table>
        <tbody>
		<tr>
            <td width="150"><label>Nomor KTP <span class="required">*</span></label></td>
            <td width="150"><input name="ktp" id="ktp"  onkeypress="return isNumberKey(event)"  size="16" maxlength="16" type="text" 
			    value="<?php echo $ktp ?>" onchange="checkKTP()"></td>
            <td class="noteLet">*Pastikan nomor ktp diisi dengan benar</td>
        </tr>
		<tr>
            <td><label >Nama Mahasiswa <span class="required">*</span></label></td>
            <td><input name="namaMahasiswa" id="namaMahasiswa" maxlength="30" type="text"/></td>
        </tr>
        <td><label>Jenis Kelamin <span class="required">*</span></label></td>
            <td>
                <select name="jenisKelamin" id="jenisKelamin">
                    <option selected="selected" value=""></option>
                    <option value="L">Laki-laki</option>
                    <option value="P">Perempuan</option>
                </select>
            </td>
        <tr>
            <td><label>Tanggal Lahir <span class="required">*</span></label></td>
            <td><input name="tanggalLahir" id="tanggalLahir" type="text" onchange="checkKTP()" value=" "/></td>
        </tr>
        <tr>
            <td><label>Password <span class="required">*</span></label></td>
            <td><input name="password" id="password" size="20" maxlength="20" type="password"></td>
        </tr>
        <tr>
            <td><label>Konfirmasi Password <span class="required">*</span></label></td>
            <td><input name="konfirmasiPassword" size="20" maxlength="20" onchange="checkPassword()" id="konfirmasiPassword" type="password"></td><td></td>
        </tr>
		</tbody>
	</table>	
	
	<h3>Fakultas dan Prodi</h3>
		
	<table>	
        <tbody>
        <tr>
            <td style="font-weight: bold">Fakultas dan Prodi</td>
            <td></td>
            <td></td>
            <td>
                <select name="Prodi" id="prodi" data-placeholder=" pilih program studi asal...">
<?php
					$dtprodi = new dt_prodi;
					$data = $dtprodi->getdata('');	
                    echo "<option selected='selected' value=''></option> ";				
					foreach ($data as $r){						
						echo "<option value=".$r['kd_prodi'].">".$r['kd_fakultas']."-".$r['prodi']."</option>
						";
					}
?>
                 </select>
            </td>
        </tr>
        <tr>
            <td><label>Tahun Masuk <span class="required">*</span></label></td>
            <td>
               <?php  
				 
				 $tmp_date =date("Y");				 
				 $txt = '<select name="tahunMasuk" id="tahunMasuk">';
				 $txt .= '<option selected="selected" value=""></option>';				
                  for ($i=2006;$i<=$tmp_date;$i++){   
                    $txt .='<option value="'.$i.'">'.$i.'</option>';                   
                  }
				 $txt .='</select>'; 
				 echo $txt;
				?>
            </td>
        </tr>

	</tbody>
	</table>	
	
    <div class="row buttons">
        <input name="yt0" value="Buat Akun" type="button" onclick="cekform()" >    </div>

    </form>
</div><!-- form -->

<script type="text/javascript" src="js/select2.js"></script>
</div><!-- content -->
<div class="clear"></div>
</div><!-- wrapper -->

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

<!-- <div id="ui-datepicker-div" class="ui-datepicker ui-widget ui-widget-content ui-helper-clearfix ui-corner-all"></div>
<script src="js/spops-2.js" charset="UTF-8" type="text/javascript"></script>
<iframe src="js/pquery-0.htm" style="display: none;"></iframe> -->
</body>
</html>
