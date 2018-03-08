<?php

require_once 'shared.php';

$nilai = isset($_POST['nilai']) ? $_POST['nilai'] : array() ;
$prodi = isset($_POST["prodi"]) ? $_POST["prodi"]: '';
$sem = isset($_POST["sem"]) ? $_POST["sem"]: 0;
$kode = isset($_POST["kode"]) ? $_POST["kode"]: '';
$shift = isset($_POST["shift"]) ? $_POST["shift"]: '';
$kelas = isset($_POST["kelas"]) ? $_POST["kelas"]: '';

$dtkrs = new dt_krs; 
$optudate= date("Y-m-d H:i:s");

if(!empty($nilai))
      {
        $NM=array('A'=>4,'B'=>3,'C'=>2,'D'=>1,'E'=>0,'T'=>0);
        foreach ($nilai as $key => $value) {
        	$data['noktphskrs']=$key;
        	$data['nilaikrs'] = $value;
        	$data['thsmskrs'] = $sem;
        	$data['prodi'] = $prodi;
        	$data['nokmkkrs'] = $kode;
        	$data['shiftkrs'] = $shift;
        	$data['kelaskrs'] = $kelas;
            $data['bobotkrs'] = $NM[$value];
            $data['opupdate'] = $kelas;
            
        	$dtkrs->update_krs($data);

        }
		
	  }
?>