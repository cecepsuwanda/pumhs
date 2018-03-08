<?php
 
 
 $server = $_SERVER['DOCUMENT_ROOT'];
 $base_path = $server . '/admin_app/';
 if(!is_dir($base_path)){
   if($server=="/home/uni10000/public_html/pumhs") {
        $base_path = $server . '/admin_app/';		
	} 
    else{
	  $base_path = $server . '/admin_app/';	 
	}  
 }
 
 include_once $base_path.'db/tb_stat_mhs.class.inc';
 

class dt_stat_mhs
{
   var $tb;
   var $numrows;  
   
    
   
   function dt_stat_mhs(){
     $this->tb = new tb_stat_mhs;
	 
   }
  
    

	function getData($where)
    {	  
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	function insert_perwalian($no_ktp,$ver_flag,$optudate,$id_opt,$kd_fak,$kd_prodi,$sem)
    {
	  $this->tb->insertRecord(array("noktp_mhs"=>$no_ktp,"statstat_mhs"=>$ver_flag,"optudate"=>$optudate,"optuid"=>$id_opt,"kd_prodi"=>$kd_prodi,"kd_fak"=>$kd_fak,"thnsmsstat_mhs"=>$sem));
	  return 1;	 
	}
	
	function delete_perwalian($no_ktp,$ver_flag,$kd_fak,$kd_prodi,$sem)
    {
	  $this->tb->deleteRecord(array("noktp_mhs"=>$no_ktp,"statstat_mhs"=>$ver_flag,"kd_prodi"=>$kd_prodi,"kd_fak"=>$kd_fak,"thnsmsstat_mhs"=>$sem));
	  return 1;	 
	}
	
	
	
	
	
}
?>


 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 