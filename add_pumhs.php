<?php
require_once "shared.php";

$username = $_SESSION["username"];
$nomorKTP = $_POST["nomorKTP"];
$password = $_SESSION["password"];


	
$dtmhs = new dt_mhs;

$data = array();

//ambil data dari form input
$Prodi = $_POST['Prodi'];
$kelas = $_POST['kelas'];
$nim = $_POST['nim'];
$namaMahasiswa = addslashes($_POST['namaMahasiswa']);
$statusMahasiswa = $_POST['statusMahasiswa'];
$jenisKelamin = $_POST['jenisKelamin'];
$tempatLahir = $_POST['tempatLahir'];
$alamat = addslashes($_POST['alamat']);
$tanggalLahir = $_POST['tanggalLahir'];
$kota = $_POST['kota'];
$telepon = $_POST['telepon'];
$provinsi = $_POST['provinsi'];
$hp = $_POST['hp'];
$kodePos = $_POST['kodePos'];
$tanggalLulus = $_POST['tanggalLulus'];
$tanggalMasuk = $_POST['tanggalMasuk'];
$ipkAkhir = $_POST['ipkAkhir'];
$tahunMasuk = $_POST['tahunMasuk'];
$nomorSkYudisium = $_POST['nomorSkYudisium'];
$batasStudi = $_POST['batasStudi'];
$tanggalYudisium = $_POST['tanggalYudisium'];
$statusAwalMahasiswa = $_POST['statusAwalMahasiswa'];
$nomorSeriIjazah = $_POST['nomorSeriIjazah'];
$smaAsal = addslashes($_POST['smaAsal']);
$universitasAsal = addslashes($_POST['universitasAsal']);
$prodiAsal = $_POST['prodiAsal'];
$sksDiakui = $_POST['sksDiakui'];
$kodePekerjaan = $_POST['kodePekerjaan'];
$namaTempatPekerjaan = addslashes($_POST['namaTempatPekerjaan']);
$mhsudate =date("Y-m-d H:i:s");
 

	$data['Kode_program_studi'] = $Prodi; 
	$data['Kelas'] = $kelas; 
	$data['NIM']= $nim; 
	$data['Nama_mahasiswa'] = $namaMahasiswa;  
	$data['Jenis_kelamin'] = $jenisKelamin;
	$data['Tempat_lahir']= $tempatLahir; 
	$data['Tanggal_lahir']= $tanggalLahir; 
	$data['Alamat'] = $alamat; 
	$data['Kode_kota'] = $kota; 
	$data['Kode_provinsi'] = $provinsi; 
	$data['Kode_pos'] = $kodePos; 
	$data['Status_mahasiswa'] =  $statusMahasiswa; 
	$data['Tahun_masuk'] = $tahunMasuk;
	$data['Batas_studi'] = $batasStudi; 
	$data['Tanggal_masuk'] = $tanggalMasuk;  
	$data['Tanggal_lulus'] = $tanggalLulus; 
	$data['IPK_akhir'] = $ipkAkhir; 
	$data['Nomor_SK_yudisium'] =  $nomorSkYudisium; 
	$data['Tanggal_SK_yudisium'] =  $tanggalYudisium; 
	$data['Nomor_seri_ijazah'] = $nomorSeriIjazah; 
	$data['Kode_prov_asal_pendidikan'] =  '999';
	$data['Status_awal_mahasiswa'] = $statusAwalMahasiswa; 
	$data['Sma_Asal'] = $smaAsal; 
	$data['Kode_perguruan_tinggi_asal'] =  $universitasAsal; 
	$data['Kode_program_studi_asal'] = $prodiAsal;
	$data['NIM_asal'] = '999999999999999'; 
	$data['SKS_diakui'] =  $sksDiakui; 
	$data['Kode_beasiswa'] =  '9999999999'; 
	$data['Kode_jenjang_pendidikan_sblm'] = 'S0'; 
	$data['Kode_pekerjaan'] = $kodePekerjaan; 
	$data['Nama_tempat_bekerja'] =  $namaTempatPekerjaan; 
	$data['Jalur_skripsi'] = '0'; 
	$data['Judul_skripsi'] = '-'; 
	$data['ID_log_audit'] = '99';
	$data['mhsudate'] = $mhsudate; 
	$data['Telepon'] = $telepon; 
	$data['HP'] = $hp;

   $data['NO_KTP']=$nomorKTP;

 
 //$result = mysql_query($sql);
 $dtmhs->update($data);
 //if ($result){	
	  echo "thanks.php";	
// } else {
// 	$file = 'sql_log.txt';
//	$current = file_get_contents($file);
//    file_put_contents($file, $current); 
//	echo "dbWarning.html";
//}
?>