<?PHP 
    require_once 'shared.php';
    if (isset($_POST["btnSubmit"])) {	

	    	
        $username    = $_POST["userName"];		
        $password    = md5($_POST["password"]);
        
        $dtopt = new dt_operator;

        		
            //masuk kalo query berhasil dieksekusi
            
            if ($dtopt->cekuser($username)) {
            	
                if ($dtopt->cekpass($dtopt->id_opt,$password)) {
					//session_start();
                    $_SESSION["userName"] = $username;
					$_SESSION["password"] = $password;
					$_SESSION["id_opt"] = $dtopt->id_opt;
					$_SESSION["fak"] = $dtopt->kd_fakultas;
					$_SESSION["lg_time"] = date("Y-m-d H:i:s");
					
					$optlog = new dt_opt_log;
					$optlog->login($_SESSION["lg_time"],$dtopt->id_opt);
				
					?>
					<script>
					    window.location="list_opt.php"; 
					</script>
					<?php
                }
                else {
					$_SESSION['userName'] = $username;
					$_SESSION['_message'] = "password_salah";
					?>
					<script>
						 window.location="index.php"; 
					</script>
					<?php
                }
            }
            else {
				$_SESSION['userName'] = $username;
				$_SESSION['_message'] = "user_tidak_terdaftar";
				
				?>
				<script>
					window.location="index.php"; 
				</script>
				<?php
            }
        
    }
    else {$_SESSION['_message'] = "user_tidak_terdaftar";};
?>