<?php

require_once 'shared.php';

$mk = isset($_POST['mk']) ? $_POST['mk'] : array() ;
$kd_prodi = isset($_POST["kd_prodi"]) ? $_POST["kd_prodi"]: '';
$ta = isset($_POST["ta"]) ? $_POST["ta"]: 0;
$kls = isset($_POST["kls"]) ? $_POST["kls"]: 'A';
$kmps = isset($_POST["kmps"]) ? $_POST["kmps"]: "BALEENDAH";
$noktp = isset($_POST["noktp"]) ? $_POST["noktp"]: '';
$optuid = isset($_SESSION["id_opt"]) ? $_SESSION["id_opt"]: '';
 
$optudate= date("Y-m-d H:i:s");

if(!empty($mk))
      {
        $dt_krs = new dt_krs;	  
	    $dt_prodi = new dt_prodi;
		$dt_mtk = new dt_mtk;				
		$dt_mhs = new dt_mhs;
		$dt_stat_mhs = new dt_stat_mhs;
		
		  $fak = $dt_prodi->get_fak($kd_prodi);
		  $dt_stat_mhs->delete_perwalian($noktp,1,$fak,$kd_prodi,$ta);
		  $dt_stat_mhs->insert_perwalian($noktp,1,$optudate,$optuid,$fak,$kd_prodi,$ta);
		  
		  $dt_krs->delete_krs(array('thsmskrs'=>$ta,'fak'=>$fak,'prodi'=>$kd_prodi,'noktphskrs'=>$noktp));
	      $dt_mhs->KTPada($noktp);
		  $shift = $dt_mhs->kelas;
		  foreach($mk as $idx=>$kdkmk)
		  {			   
			$sem = $dt_mtk->carisem($ta,$fak,$kd_prodi,$kdkmk);             			
           	$dt_krs->save_krs(array('thsmskrs'=>$ta,'fak'=>$fak,'prodi'=>$kd_prodi,'semkrs'=>$sem,'shiftkrs'=>$shift,'kelaskrs'=>$kls,'nokmkkrs'=>$kdkmk,'noktphskrs'=>$noktp,'kampus'=>$kmps,'optudate'=>$optudate,'optuid'=>$optuid));
            if($dt_mtk->kd_lab!="-"){			  
			  $dt_krs->save_krs(array('thsmskrs'=>$ta,'fak'=>$fak,'prodi'=>$kd_prodi,'semkrs'=>$sem,'shiftkrs'=>$shift,'kelaskrs'=>$kls,'nokmkkrs'=>$dt_mtk->mtk_no,'noktphskrs'=>$noktp,'kampus'=>$kmps,'optudate'=>$optudate,'optuid'=>$optuid));
            }			  
						
		  }
		
	  }
?>