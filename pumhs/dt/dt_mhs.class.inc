<?php
 require_once dirname(dirname(dirname(__FILE__))).'/shared.php';
class dt_mhs
{
   var $tb;
   var $tb_view;
   var $numrows;  
   
   var $ktp;
   var $prod; 
   var $Nama_mahasiswa;
   var $jenisKelamin;
   var $tanggalLahir;
   var $tahunMasuk;
   var $kelas;
   var $nim;
   var $status;
   var $status_awl;
   var $tempatLahir;
   var $alamat;
   var $kota;
   var $telepon;
   var $provinsi;
   var $hp;
   var $kodePos;
   var $tanggalLulus;
   var $tanggalMasuk;
   var $ipkAkhir;
   var $nomorSkYudisium;
   var $batasStudi;
   var $tanggalYudisium;
   var $nomorSeriIjazah;
   var $smaAsal;
   var $sksDiakui;
   var $namaTempatPekerjaan;
   var $kodePekerjaan;
   var $prodiAsal;
   var $universitasAsal;
   var $pass;
   var $optcdate;
   var $optcid; 
   var $optudate;
   var $optuid;
   var $verifikasi; 
   
   function __construct(){
     $this->tb = new tb_mhs;
	 $this->tb_view = new tb_view_mhs;
   }

   function insert($data)
   {
    $this->tb->insertRecord($data);
   }

   function update($data)
   {
    $this->tb->updateRecord($data);
   }   

   function tgl_log($ktp)
   {
     $data=array();
     $data['NO_KTP']=$ktp;
     $data['Tgl_Log']=date("Y-m-d H:i:s");
     $this->tb->updaterecord($data);
   }
  
    function getJml($where)
    {	  
	  
	  $this->tb->sql_select ="*";
	  
	  $this->tb->tablename ="tmst_mahasiswa left join tmst_prodi on kode_program_studi = kd_prodi";
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $this->numrows;		 
	  	  
	}

	function getData($where)
    {	  
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	function KTPada($ktp)
	{
	  
	  $data = $this->getData("NO_KTP = '".$ktp."'");
	  
	  if(!empty($data)){
	    foreach($data as $row){
			  $this->prod = $row['Kode_program_studi']; 
			  $this->Nama_mahasiswa = $row['Nama_mahasiswa'];
			  $this->jenisKelamin  = $row['Jenis_kelamin'];
			  $this->tanggalLahir  = $row['Tanggal_lahir'];
			  $this->tahunMasuk  = $row['Tahun_masuk'];
			  $this->kelas = $row['Kelas'];
			  $this->nim  = $row['NIM'];
			  $this->status  = $row['Status_mahasiswa'];
			  $this->status_awl  = $row['Status_awal_mahasiswa'];
			  $this->tempatLahir  = $row['Tempat_lahir'];
			  $this->alamat  = $row['Alamat'];
			  $this->kota  = $row['Kode_kota'];
			  $this->telepon  = $row['Telepon'];
			  $this->provinsi  = $row['Kode_provinsi'];
			  $this->hp  = $row['HP'];
			  $this->kodePos  = $row['Kode_pos'];
			  $this->tanggalLulus  = $row['Tanggal_lulus'];
			  $this->tanggalMasuk  = $row['Tanggal_masuk'];
			  $this->ipkAkhir  = $row['IPK_akhir'];
			  $this->nomorSkYudisium  = $row['Nomor_SK_yudisium'];
			  $this->batasStudi  = $row['Batas_studi'];
			  $this->tanggalYudisium  = $row['Tanggal_SK_yudisium'];
			  $this->nomorSeriIjazah  = $row['Nomor_seri_ijazah'];
			  $this->smaAsal  = $row['Sma_Asal'];
			  $this->sksDiakui  = $row['SKS_diakui'];
			  $this->namaTempatPekerjaan  = $row['Nama_tempat_bekerja'];
			  $this->kodePekerjaan  = $row['Kode_pekerjaan'];
			  $this->prodiAsal  = $row['Kode_program_studi_asal'];
			  $this->universitasAsal  = $row['Kode_perguruan_tinggi_asal'];
			  $this->pass = $row['password'];
			  $this->verifikasi = $row['verifikasi'];
			  $this->ktp = $row['NO_KTP'];
		}	  
	  }
	  
	  return $this->numrows>0; 
	}
	
		
	function getDataEntri($where)
    {	  
	  
	  $this->tb->sql_select ="*";
	  $this->tb->sql_groupby ="";
	  $this->tb->sql_orderby ="";
	  $this->tb->sql_having ="";
	  
	  
	  $this->tb->tablename ="tmst_mahasiswa left join tmst_prodi on kode_program_studi = kd_prodi";
	  
	  $this->tb->sql_orderby = "mhscdate desc";
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}	
	
	function getDataView($idx)
    {	  
	  switch($idx){  
	   case 0 :	$this->tb_view->tablename ="mhs_blmvalid left join tmst_prodi on kode_program_studi = kd_prodi";
	            break;
	   case 1 :	$this->tb_view->tablename ="mhs_valid left join tmst_prodi on kode_program_studi = kd_prodi";
	            break;
       case 2 :	$this->tb_view->tablename ="mhs_process left join tmst_prodi on kode_program_studi = kd_prodi";
	            break; 
       case 3 :	$this->tb_view->tablename ="mhs_terverifikasi left join tmst_prodi on kode_program_studi = kd_prodi";
	            break;
       case 4 :	$this->tb_view->tablename ="mhs_tdklls left join tmst_prodi on kode_program_studi = kd_prodi";
	            break;				
	  }	  
	  $data = $this->tb_view->getData(""); 
	 
	  $this->numrows=$this->tb_view->numrows;
      	 
	  return $data;		 
	  	  
	}	
	
	function getActivitasHariIni($idx)
	{
	
	  switch($idx){  
	   case 1 :	$this->tb_view->tablename ="mhs_create left join tmst_prodi on kode_program_studi = kd_prodi";
	            break;
	   case 2 :	$this->tb_view->tablename ="mhs_update left join tmst_prodi on kode_program_studi = kd_prodi";
	            break;
       case 3 :	$this->tb_view->tablename ="mhs_login left join tmst_prodi on kode_program_studi = kd_prodi";
	            break;        			
	  }	  
	  $data = $this->tb_view->getData(""); 
	 
	  $this->numrows=$this->tb_view->numrows;
      	 
	  return $data;		
	
	}
	
	function ubahpass($ktp,$pass)
	{
	  $this->tb->updateRecord(array("NO_KTP"=>$ktp,"password"=>$pass));
	  $this->getData("NO_KTP = '".$ktp."' and password='".$pass."'");
	  
	  return $this->numrows>0;
	}
	
	function update_verifikasi($no_ktp,$ver_flag,$optudate,$optuid)
    {
	  
	  $this->tb->updateRecord(array("NO_KTP"=>$no_ktp,"verifikasi"=>$ver_flag,"optudate"=>$optudate ,"optuid"=>$optuid));
	  return 1;	 
	}
	
	function update_validasi($no_ktp,$valid)
    {
	  $this->tb->updateRecord(array("NO_KTP"=>$no_ktp,"validasi"=>$valid));
	  return 1;	 
	}
	
	function update_tgl_msk($no_ktp,$tgl)
    {
	  $this->tb->updateRecord(array("NO_KTP"=>$no_ktp,"Tanggal_masuk"=>$tgl));
	  return 1;	 
	}
	
	function is_nim_double($nim)
    {
      $this->tb->sql_select ="nim,COUNT(nim) jml";
	  $this->tb->sql_groupby ="nim";
	  $this->tb->sql_orderby ="";
	  $this->tb->sql_having ="";
	  $this->tb->tablename ="tmst_mahasiswa";	  
	  $data = $this->tb->getData("verifikasi=1 and nim='".$nim."'");	 
	  $jml=0;
	  if(!empty($data)){ 	  
		  foreach($data as $row){
		   $jml = $row['jml'];
		  }
	   }
	  return $jml>=2;	  
	}
	
	function is_nm_double($nama)
    {
      $this->tb->sql_select ="trim(Nama_mahasiswa),COUNT(trim(Nama_mahasiswa)) jml";
	  $this->tb->sql_groupby ="trim(Nama_mahasiswa)";
	  $this->tb->sql_orderby ="";
	  $this->tb->sql_having ="";
	  $this->tb->tablename ="tmst_mahasiswa";	  
	  $data = $this->tb->getData("verifikasi=1 and trim(Nama_mahasiswa)=trim('".$nama."')");	 
	  $jml=0;
	  if(!empty($data)){ 	  
		  foreach($data as $row){
		   $jml = $row['jml'];
		  }
	   }
	  return $jml>=2;	  
	}
	
	function getdataStat($where)
    {
	  
	   
	   $dt_fak_jn_prodi = new dt_fak_jn_prodi;
	   $stat_struct = array();
	   

	 $this->tb->sql_select ="Kode_program_studi as kd_prodi , 
								  Tahun_masuk,
								  COUNT(`tmst_mahasiswa`.`NO_KTP`) AS `jmlttl`,
								  SUM(IF(((`tmst_mahasiswa`.`validasi` = 0) AND (`tmst_mahasiswa`.`verifikasi` = 0) AND (`tmst_mahasiswa`.`nm_file` = '')),1,0)) AS `jmlblmlyk`,  
								  SUM(IF(((`tmst_mahasiswa`.`validasi` = 1) AND (`tmst_mahasiswa`.`verifikasi` = 0) AND (`tmst_mahasiswa`.`nm_file` = '')),1,0)) AS `jmlval`,
								  SUM(IF(((`tmst_mahasiswa`.`verifikasi` = 0) AND (`tmst_mahasiswa`.`validasi` = 1) AND (`tmst_mahasiswa`.`nm_file` <> '')),1,0)) AS `jmlsdver`,
								  SUM(IF((`tmst_mahasiswa`.`verifikasi` = 1),1,0)) AS `jmlver`,
								  SUM(IF((`tmst_mahasiswa`.`verifikasi` = 2),1,0)) AS `jmlnotver`";
	  $this->tb->sql_groupby =" Kode_program_studi,Tahun_masuk"; //`tmst_prodi`.`kd_fakultas`,
	  $this->tb->sql_orderby ="";
	  $this->tb->sql_having ="";
	  $this->tb->tablename ="tmst_mahasiswa";
	  
	  
	  $data = $this->tb->getdata("");  
	  
	  if(!empty($data))
	  {
	    
		foreach($data as $row)
		{
		  $dt_fak=$dt_fak_jn_prodi->getnmfk($row['kd_prodi']);
		  	  
		  $stat_struct['jmlttl'][$dt_fak['kd_fak']]['nm_fak']=$dt_fak['nm_fak'];
		  $stat_struct['jmlttl'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']]
		  =  isset($stat_struct['jmlttl'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']]) ? $stat_struct['jmlttl'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']] + $row['jmlttl'] : $row['jmlttl'] ;
		  
		  $stat_struct['jmlblmlyk'][$dt_fak['kd_fak']]['nm_fak']=$dt_fak['nm_fak'];
		  $stat_struct['jmlblmlyk'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']]
		  = isset($stat_struct['jmlblmlyk'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']]) ? $stat_struct['jmlblmlyk'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']]+ $row['jmlblmlyk'] : $row['jmlblmlyk'];
		  
		  $stat_struct['jmlval'][$dt_fak['kd_fak']]['nm_fak']=$dt_fak['nm_fak'];
		  $stat_struct['jmlval'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']]
		  = isset($stat_struct['jmlval'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']]) ?  $stat_struct['jmlval'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']] + $row['jmlval'] : $row['jmlval'];
		  
		  $stat_struct['jmlsdver'][$dt_fak['kd_fak']]['nm_fak']=$dt_fak['nm_fak'];
		  $stat_struct['jmlsdver'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']]
		  = isset($stat_struct['jmlsdver'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']]) ? $stat_struct['jmlsdver'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']] + $row['jmlsdver'] : $row['jmlsdver'];
          
          $stat_struct['jmlver'][$dt_fak['kd_fak']]['nm_fak']=$dt_fak['nm_fak'];
		  $stat_struct['jmlver'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']]
		  = isset($stat_struct['jmlver'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']]) ? $stat_struct['jmlver'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']] + $row['jmlver']  : $row['jmlver'];

		  $stat_struct['jmlnotver'][$dt_fak['kd_fak']]['nm_fak']=$dt_fak['nm_fak'];
		  $stat_struct['jmlnotver'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']]
		  =isset($stat_struct['jmlnotver'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']]) ?  $stat_struct['jmlnotver'][$dt_fak['kd_fak']]['Tahun_Masuk'][$row['Tahun_masuk']]+$row['jmlnotver'] : $row['jmlnotver'];

		  
		}
	  }
	  
	  
	  return $stat_struct;
	}
	
}
?>


 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 