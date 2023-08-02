-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
-- -----------------------------------------------------
-- Schema DB1
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema DB1
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `DB1` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci ;
USE `DB1` ;

-- -----------------------------------------------------
-- Table `DB1`.`Login`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `DB1`.`Login` (
  `id_login` INT NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id_login`),
  UNIQUE INDEX `id_login_UNIQUE` (`id_login` ASC) VISIBLE)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `DB1`.`Main Page`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `DB1`.`Main Page` (
  `id_main` INT NOT NULL AUTO_INCREMENT,
  `Login_id_login` INT NOT NULL,
  PRIMARY KEY (`id_main`),
  UNIQUE INDEX `id_main_UNIQUE` (`id_main` ASC) VISIBLE,
  INDEX `fk_Main Page_Login1_idx` (`Login_id_login` ASC) VISIBLE,
  CONSTRAINT `fk_Main Page_Login1`
    FOREIGN KEY (`Login_id_login`)
    REFERENCES `DB1`.`Login` (`id_login`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `DB1`.`Category`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `DB1`.`Category` (
  `id_category` INT NOT NULL AUTO_INCREMENT,
  `Main Page_id_main` INT NOT NULL,
  PRIMARY KEY (`id_category`),
  UNIQUE INDEX `id_category_UNIQUE` (`id_category` ASC) VISIBLE,
  INDEX `fk_Category_Main Page1_idx` (`Main Page_id_main` ASC) VISIBLE,
  CONSTRAINT `fk_Category_Main Page1`
    FOREIGN KEY (`Main Page_id_main`)
    REFERENCES `DB1`.`Main Page` (`id_main`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `DB1`.`Contents`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `DB1`.`Contents` (
  `id_cont` INT NOT NULL AUTO_INCREMENT,
  `Main Page_id_main` INT NOT NULL,
  `Contents_id_cont` INT NOT NULL,
  PRIMARY KEY (`id_cont`),
  UNIQUE INDEX `id_cont_UNIQUE` (`id_cont` ASC) VISIBLE,
  INDEX `fk_Contents_Main Page_idx` (`Main Page_id_main` ASC) VISIBLE,
  INDEX `fk_Contents_Contents1_idx` (`Contents_id_cont` ASC) VISIBLE,
  CONSTRAINT `fk_Contents_Contents1`
    FOREIGN KEY (`Contents_id_cont`)
    REFERENCES `DB1`.`Contents` (`id_cont`),
  CONSTRAINT `fk_Contents_Main Page`
    FOREIGN KEY (`Main Page_id_main`)
    REFERENCES `DB1`.`Main Page` (`id_main`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `DB1`.`Category_has_Contents`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `DB1`.`Category_has_Contents` (
  `Category_id_category` INT NOT NULL,
  `Contents_id_cont` INT NOT NULL,
  PRIMARY KEY (`Category_id_category`, `Contents_id_cont`),
  INDEX `fk_Category_has_Contents_Contents1_idx` (`Contents_id_cont` ASC) VISIBLE,
  INDEX `fk_Category_has_Contents_Category1_idx` (`Category_id_category` ASC) VISIBLE,
  CONSTRAINT `fk_Category_has_Contents_Category1`
    FOREIGN KEY (`Category_id_category`)
    REFERENCES `DB1`.`Category` (`id_category`),
  CONSTRAINT `fk_Category_has_Contents_Contents1`
    FOREIGN KEY (`Contents_id_cont`)
    REFERENCES `DB1`.`Contents` (`id_cont`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `DB1`.`TB1`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `DB1`.`TB1` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `name` VARCHAR(16) NOT NULL,
  `msg` VARCHAR(32) NULL DEFAULT 'no message',
  PRIMARY KEY (`id`))
ENGINE = InnoDB
AUTO_INCREMENT = 2
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


-- -----------------------------------------------------
-- Table `DB1`.`user`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `DB1`.`user` (
  `uid` INT NOT NULL AUTO_INCREMENT,
  `user_id` VARCHAR(45) NOT NULL,
  `user_pwd` VARCHAR(45) NOT NULL,
  `Login_id_login` INT NOT NULL,
  PRIMARY KEY (`uid`),
  UNIQUE INDEX `uid_UNIQUE` (`uid` ASC) VISIBLE,
  UNIQUE INDEX `user_id_UNIQUE` (`user_id` ASC) VISIBLE,
  INDEX `fk_user_Login1_idx` (`Login_id_login` ASC) VISIBLE,
  CONSTRAINT `fk_user_Login1`
    FOREIGN KEY (`Login_id_login`)
    REFERENCES `DB1`.`Login` (`id_login`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb4
COLLATE = utf8mb4_0900_ai_ci;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
