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
 
 include_once $base_path.'db/tb_kec.class.inc';
 

class dt_kec
{
   var $tb;
   var $numrows;  
  
   function dt_kec(){
     $this->tb = new tb_kec;
	 
   }
  
	function getData($where)
    {	  
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	function cek_kec($no_ktp)
	{
      
	 $this->getData('kode_kab_kota like "'.substr($no_ktp,0,4).'%"');
	  
	 if($this->tb->numrows>0)
	 {
	   return 1;
	 }else
	 {
	   return 0;
	 } 
	
	}
	
	
}
?>