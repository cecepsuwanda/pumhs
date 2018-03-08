<?php
require_once dirname(dirname(__FILE__)).'/shared.php';
	
$ktp = $_POST['nomorKTP'];
$password = md5($_POST['password']);
		
$dt_mhs = new dt_mhs;		
		
		if($dt_mhs->KTPada($ktp))
		{		
			 	 
			  if($dt_mhs->ubahpass($ktp,$password)){
			  ?>
	            <script>
		           window.location="thanks.php";
	            </script>
	           <?php
			  }else{
			  	?>
	            <script>
		           window.location="dbwarning.html";
	            </script>
	           <?php		  
			  }
		   
		}else
			{
			  	?>
	            <script>
		           window.location="dbwarning.html";
	            </script>
	           <?php		  
			  
			}
		
?>