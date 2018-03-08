<?php 

include_once "shared.php";


$idx = $_POST['idx'];

switch($idx){
 	
case 1 :    $vwmtk = new vw_mtk; 
            echo $vwmtk->filter_prodi();
			break;		
case 2 :    
            $kd_prodi = isset($_POST['kd_prodi']) ? $_POST['kd_prodi'] : "";
			$vwmtk = new vw_mtk; 
            echo $vwmtk->hsl_filter_prodi($kd_prodi);
			break;	
case 3 :    
            $kd_prodi = isset($_POST['kd_prodi']) ? $_POST['kd_prodi'] : "";
			$ta = isset($_POST['ta']) ? $_POST['ta'] : 0;
			$nta = isset($_POST['nta']) ? $_POST['nta'] : "";
			$noktp=isset($_POST['noktp']) ? $_POST['noktp'] : "";
			$vwmtk = new vw_mtk; 
            echo $vwmtk->tbl_krs_mdl1($kd_prodi,$ta,$nta,$noktp);
			break;			
}			

?>