<?php 

require_once dirname(dirname(__FILE__)).'/shared.php';

$idx = $_POST['idx'];

switch($idx){
case 1 :    $vwmhs = new vw_mhs; 
            echo $vwmhs->entry_data1();
			break;	
case 2 :
            $vwmhs = new vw_mhs;
			$txt="<fieldset>";
			$txt.="<legend>Keterangan :</legend>";
			$txt.="1. Data belum layak verifikasi dikarenakan hasil validasi menyatakan data belum lengkap. <br>";
			$txt.="2. Data layak verifikasi dikarenakan hasil validasi menyatakan data lengkap. <br>";
			$txt.="3. Data lolos verifikasi bila Program Studi mengakui kebenaran data yang diinput. <br>";
			$txt.="4. Data tidak lolos verifikasi bila Program Studi tidak mengakui kebenaran data yang diinput. <br>";
			$txt.="5. Data yang diberi warna, diinput oleh operator fakultas, hanya operator fakultas yang bisa merubah data tersebut. <br>";
			$txt.="</fieldset><br>";
			$txt.="<fieldset>";
			$txt.=$vwmhs->activitas_hari_ini();
			$txt.="</fieldset>";
			echo $txt;
			break;
case 3 :    $vwmhs = new vw_mhs; 
            echo $vwmhs->lst_entry_data(0,"lst_mhs2"); 
			break;
case 4 :    $vwmhs = new vw_mhs; 
            echo $vwmhs->lst_entry_data(1,"lst_mhs3");
			break;
case 5 :    $vwmhs = new vw_mhs; 
            echo $vwmhs->lst_entry_data(2,"lst_mhs4");
			break;
case 6 :    $vwmhs = new vw_mhs; 
            echo $vwmhs->lst_entry_data(3,"lst_mhs5");
			break;
case 7 :    $vwmhs = new vw_mhs; 
            echo $vwmhs->lst_entry_data(4,"lst_mhs6");
			break;	
case 8 :    $vwkrs = new vw_krs; 
            echo $vwkrs->list_mhs();
			break;
case 9 :    $vwkrs = new vw_krs; 
            echo $vwkrs->list_mtk();
			break;			
case 10 :    $vwkrs = new vw_krs; 
             $prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
            echo $vwkrs->filter_mhs($prodi);
			break;	
case 11 :    $vwkrs = new vw_krs; 
             $prodi = isset($_POST['prodi']) ? $_POST['prodi'] : "";
            echo $vwkrs->filter_mtk($prodi);
			break;				
}			

?>

 
     
  	 
  	 