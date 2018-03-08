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
 
 include_once $base_path.'db/tb_epsbed_mhs.class.inc';
 

class dt_mhs_epsbed
{
   var $tb;
   var $numrows;  
   
 
   
   function dt_mhs_epsbed(){
     $this->tb = new tb_epsbed_mhs;
	 
   }
     
	 function getData($where)
    {	  
	  
	  $data = $this->tb->getData($where); 
	 
	  $this->numrows=$this->tb->numrows;
      	 
	  return $data;		 
	  	  
	}
	
	function is_exist($nim,$nama)
    {
      $data = $this->tb->getData("nimhsmsmhs='".$nim."' and nmmhsmsmhs='".$nama."'");	 
	  
	  return $this->tb->numrows>=1;	  
	}
	
	
}
?>


 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 