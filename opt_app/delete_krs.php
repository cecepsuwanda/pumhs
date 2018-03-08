<?php 
require_once 'shared.php';

$sem = isset($_POST['sem']) ? $_POST['sem'] : 0;
$prodi = isset($_POST["prodi"]) ? $_POST["prodi"]: '';
$fak = isset($_POST["fak"]) ? $_POST["fak"]: 0;
$noktp = isset($_POST["noktp"]) ? $_POST["noktp"]: 'A';

$dt_krs = new dt_krs;
$dt_krs->delete_krs(array('thsmskrs'=>$sem,'fak'=>$fak,'prodi'=>$prodi,'noktphskrs'=>$noktp));

$dt_stat_mhs = new dt_stat_mhs;
$optudate= date("Y-m-d H:i:s");
$dt_stat_mhs->delete_perwalian($noktp,1,$fak,$prodi,$sem);
$dt_stat_mhs->insert_perwalian($noktp,5,$optudate,'system',$fak,$prodi,$sem);

?>