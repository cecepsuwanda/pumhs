<?php
	require_once 'shared.php';
	
	$dtmhs = new dt_mhs;

//ambil data dari form input
$ktp = $_POST['ktp'];
$password = md5($_POST['password']);
$Prodi = $_POST['Prodi'];
$namaMahasiswa = addslashes($_POST['namaMahasiswa']);
$jenisKelamin = $_POST['jenisKelamin'];
$tanggalLahir = $_POST['tanggalLahir'];
$tahunMasuk = $_POST['tahunMasuk'];
    	
		
		if($dtmhs->KTPada($ktp)){	
		   $_SESSION['ktp'] = $ktp;
		   $_SESSION['password'] = $password;
		   $_SESSION['_message'] = "sudah ada";
		?>
		<script>
			window.location="index.php";
		</script>
		<?php
		}else
			{		
			  if($ktp!=""){  
				 $data = array();
				 $data['NO_KTP'] =$ktp;
				 $data['password']=$password;
				 $data['Kode_perguruan_tinggi']='1409';
				 $data['Kode_program_studi']=$Prodi;
				 $data['Nama_mahasiswa']=$namaMahasiswa;
				 $data['Jenis_kelamin']=$jenisKelamin;
				 $data['Tanggal_lahir']=$tanggalLahir;
				 $data['Tahun_masuk']=$tahunMasuk;
				 $data['nm_file']='';
				 $data['mhscdate']=date("Y-m-d H:i:s");

                 $dtmhs->insert($data);
				 //$result = mysql_query($sql);
			 	 //if ($result){
					$_SESSION['ktp'] = $ktp;
					$_SESSION['_message'] = "lengkapi_data";
					include "thanks.php";
				 //} else {
				   // $file = 'sql_log.txt';
	               // $current = file_get_contents($file);
	               // $current .=date("Y-m-d H:i:s").",".$sql."\n";
                   // file_put_contents($file, $current); 
					//include "dbWarning.html";
				 //}
			  }else{
			     $file = 'sql_log.txt';
	             $current = file_get_contents($file);
	             $current .= date("Y-m-d H:i:s").",".$sql."\n";
                 file_put_contents($file, $current);
			     include "dbWarning.html";
			  } 
			}
		
?>