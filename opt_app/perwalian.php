<?php

require_once 'shared.php';

$id_opt = isset($_SESSION["id_opt"]) ? $_SESSION["id_opt"]: '';
$ver = isset($_POST['ver']) ? $_POST['ver'] : '' ;
$kd_fak = isset($_POST["kd_fak"]) ? $_POST["kd_fak"]: '';
$kd_prodi = isset($_POST["kd_prodi"]) ? $_POST["kd_prodi"]: '';
$sem = isset($_POST["sem"]) ? $_POST["sem"]: 0;
$optudate= date("Y-m-d H:i:s");

if(!empty($ver))
      {
        $dt_stat_mhs = new dt_stat_mhs;	  
	    
	      foreach($ver as $no_ktp=>$ver_flag)
		  {		   
           	$dt_stat_mhs->delete_perwalian($no_ktp,$ver_flag,$kd_fak,$kd_prodi,$sem);
			$dt_stat_mhs->insert_perwalian($no_ktp,$ver_flag,$optudate,$id_opt,$kd_fak,$kd_prodi,$sem);
           			
		  }
		
	  }
?>