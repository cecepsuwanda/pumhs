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
 
 include_once $base_path.'db/tb_admin_log.class.inc';
 

class dt_admin_log
{
   var $tb;
   var $numrows;  
  
   function dt_admin_log(){
     $this->tb = new tb_admin_log;
	 
   }
  
	function getData($where)
    {	  
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	function logout($lg_time,$id)
   {       
	   $this->tb->updateRecord(array('lg_time'=>$lg_time,'user'=>$id,'out_time'=>date("Y-m-d H:i:s")));
	   return 1;
   }
	
	
}
?>