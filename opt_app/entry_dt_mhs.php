<?php

require_once 'shared.php';

$id_opt = isset($_SESSION["id_opt"]) ? $_SESSION["id_opt"]: '';
$idx = $_POST['idx'];

$dt_mhs = new dt_mhs;
              
			  $dt_mhs->ktp = $_POST['ktp'];
			  $dt_mhs->pass = md5($dt_mhs->ktp);
			  $dt_mhs->prod = $_POST['Prodi']; 
			  $dt_mhs->Nama_mahasiswa = $_POST['namaMahasiswa'];
			  $dt_mhs->jenisKelamin  = $_POST['jenisKelamin'];
			  $dt_mhs->tanggalLahir  = $_POST['tanggalLahir'];
			  $dt_mhs->tahunMasuk  = $_POST['tahunMasuk'];
			  $dt_mhs->kelas = $_POST['kelas'];
			  $dt_mhs->nim  = $_POST['nim'];
			  $dt_mhs->status  = $_POST['statusMahasiswa'];
			  $dt_mhs->status_awl  = $_POST['statusAwalMahasiswa'];
			  $dt_mhs->tempatLahir  = $_POST['tempatLahir'];
			  $dt_mhs->alamat  = $_POST['alamat'];
			  $dt_mhs->kota  = $_POST['kota'];
			  $dt_mhs->telepon  = $_POST['telepon'];
			  $dt_mhs->provinsi  = $_POST['provinsi'];
			  $dt_mhs->hp  = $_POST['hp'];
			  $dt_mhs->kodePos  = $_POST['kodePos'];
			  $dt_mhs->tanggalLulus  = $_POST['tanggalLulus'];
			  
			  $parts = explode("-",$_POST['tanggalMasuk']);
			  if( ($_POST['tahunMasuk']!="0000") && ($_POST['tanggalMasuk'] != null) && ($parts[0]!=$_POST['tahunMasuk'])){
		         if($row['Tanggal_masuk'] == "0000-00-00"){	  
         			  $dt_mhs->tanggalMasuk  = $_POST['tahunMasuk']."-09-23";		  
			      }else{  
			     	$dt_mhs->tanggalMasuk  = $_POST['tahunMasuk']."-".$parts[1]."-".$parts[2];
			      }
			  }	  
			  $dt_mhs->ipkAkhir  = $_POST['ipkAkhir'];
			  $dt_mhs->nomorSkYudisium  = $_POST['nomorSkYudisium'];
			  $dt_mhs->batasStudi  = $_POST['batasStudi'];
			  $dt_mhs->tanggalYudisium  = $_POST['tanggalYudisium'];
			  $dt_mhs->nomorSeriIjazah  = $_POST['nomorSeriIjazah'];
			  $dt_mhs->smaAsal  = $_POST['smaAsal'];
			  $dt_mhs->sksDiakui  = $_POST['sksDiakui'];
			  $dt_mhs->namaTempatPekerjaan  = $_POST['namaTempatPekerjaan'];
			  $dt_mhs->kodePekerjaan  = $_POST['kodePekerjaan'];
			  $dt_mhs->prodiAsal  = $_POST['prodiAsal'];
			  $dt_mhs->universitasAsal  = $_POST['universitasAsal'];
			  $dt_mhs->optcdate= date("Y-m-d H:i:s");
              $dt_mhs->optcid=$id_opt; 
              $dt_mhs->optudate= date("Y-m-d H:i:s");
              $dt_mhs->optuid=$id_opt; 

switch($idx)
{

  case 1 : 
          
		  $hsl = $dt_mhs->tambah();
		  switch($hsl) 
		  { 
		   case 0 : echo "Mahasiswa dengan ktp=$dt_mhs->ktp sudah ada !!!";break;
		   case 1 : echo "Data Mahasiswa Berhasil Disimpan !!!";break;
          }
		  break;
  case 2 : 
          
		  $hsl = $dt_mhs->edit();
		  switch($hsl) 
		  { 
		   case 0 : echo "Data Mahasiswa gagal diedit !!!";break;
		   case 1 : echo "Data Mahasiswa Berhasil Diedit !!!";break;
          }
		  
          break;
  case 3 : 
         
		  $hsl = $dt_mhs->hapus();
		  echo "Data Mahasiswa Berhasil Dihapus !!!";
          break;
		  

}  


?>