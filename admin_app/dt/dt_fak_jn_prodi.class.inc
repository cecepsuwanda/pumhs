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
 
 include_once $base_path.'db/tb_fak_jn_prodi.class.inc';
 

class dt_fak_jn_prodi
{
   var $tb;
   var $numrows;  
  
   function dt_fak_jn_prodi(){
     $this->tb = new tb_fak_jn_prodi;
	 
   }
  

	function getData($where)
    {	  
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	
}
?>