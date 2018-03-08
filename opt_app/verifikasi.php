<?php

require_once 'shared.php';

$id_opt = isset($_SESSION["id_opt"]) ? $_SESSION["id_opt"]: '';
$ver = isset($_POST['ver']) ? $_POST['ver'] : '' ;
$kd_fak = isset($_POST["kd_fak"]) ? $_POST["kd_fak"]: '';
$optudate= date("Y-m-d H:i:s");

if(!empty($ver))
      {
        $dt_mhs = new dt_mhs;	  
	    
	      foreach($ver as $no_ktp=>$ver_flag)
		  {		   
           	$dt_mhs->update_verifikasi($no_ktp,$ver_flag,$optudate,$id_opt);
           			
		  }
		
	  }
?>