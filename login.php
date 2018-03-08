<?PHP    
    require_once "shared.php";
    if (isset($_POST["btnSubmit"])) {
	
		//session_start();
		//$_SESSION["usr"] = "root";
		
		
        $username    = $_POST["nomorKTP"];
        $password    = md5($_POST["password"]);
        
        $dtmhs = new dt_mhs;

        
        if ($dtmhs->KTPada($username)) {
            //masuk kalo query berhasil dieksekusi
                        
                if ($password == $dtmhs->pass) {
					//session_start();
                    $_SESSION["username"] = $username;
					$_SESSION["nomorKTP"] = $dtmhs->ktp;
                    $_SESSION["password"] = $password;
					
					$dtmhs->tgl_log($username);
					
					?>
					<script>
						window.location="form_add_pumhs.php";
					</script>
					<?php
                }
                else {
					$_SESSION['ktp'] = $username;
					$_SESSION['_message'] = "password_salah";
					?>
					<script>
						window.location="index.php";
					</script>
					<?php
                }
            }
            else {
				$_SESSION['ktp'] = $username;
				$_SESSION['_message'] = "identitas_salah";
				?>
				<script>
					window.location="form_add_pumhs_acc.php";
				</script>
				<?php
            }
        
    }
    else header("index.php");
?>